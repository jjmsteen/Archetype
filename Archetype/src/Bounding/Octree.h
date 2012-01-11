#pragma once

#include "libPrefix.h"

#include <vector>
#include <set>

#include "Vector3.h"
#include "BoundingAABB.h"
#include "BoundingFrustum.h"
#include "Mesh.h"
#include "MeshAlias.h"

namespace AT
{
namespace Bounding
{

class Octree
{
	static unsigned int maxRecursionDepth;

	// Node names based on a right handed coordinate system
	// looking down the negative Z axis
	enum OctreeNodes
	{
		FRONT_TOP_LEFT,
		FRONT_TOP_RIGHT,
		FRONT_BOTTOM_LEFT,
		FRONT_BOTTOM_RIGHT,
		BACK_TOP_LEFT,
		BACK_TOP_RIGHT,
		BACK_BOTTOM_LEFT,
		BACK_BOTTOM_RIGHT,
	};

	// The central point of this node
	Maths::Vector3 centre;

	// The length of one side of the node (stored for reference)
	float sideLength;

	// The bounding box for the node
	BoundingAABB boundingBox;

	// Current recursion depth
	unsigned int nodeDepth;

	// The branches of this octree node
	Octree * nodes[8];
	
	// A set of meshes to draw
	std::set<Model::MeshAlias *> meshes;

public:

#pragma region Static Methods

	DLLEXPORT static void SetMaxRecursionDepth(unsigned int maxDepth);

#pragma endregion

#pragma region Constructors / Destructor

	DLLEXPORT Octree(const Maths::Vector3 & centre = Maths::Vector3(), float sideLength = 1000);

#pragma region Private Constructors

	DLLEXPORT Octree(unsigned int nodeDepth, const Maths::Vector3 & centre, float sideLength);

#pragma endregion

	DLLEXPORT ~Octree(void);

#pragma endregion
    
#pragma region Getters and Setters
    
    DLLEXPORT float GetSideLength() const { return sideLength; }
    
#pragma endregion

#pragma region Octree Routines

	DLLEXPORT void AddMesh(Model::MeshAlias * mesh);

	DLLEXPORT std::set<Model::MeshAlias *> GetVisibleMeshes(const BoundingFrustum & bf) const;

	DLLEXPORT std::set<Model::MeshAlias *> GetAllMeshes() const;

private: 

	DLLEXPORT void CreateNode(int index);

	DLLEXPORT void CreateAllNodes();

#pragma endregion

};

}
}