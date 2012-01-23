#include "stdafx.h"
#include "Octree.h"

using namespace AT;
using namespace Bounding;

#pragma region Static Methods

unsigned int Octree::maxRecursionDepth;

void Octree::SetMaxRecursionDepth(unsigned int maxDepth)
{
	// Ensure there is at least one level
	if (maxDepth < 1) maxDepth = 1;

	// Set the depth
	Octree::maxRecursionDepth = maxDepth;
}

#pragma endregion

#pragma region Constructors / Destructor

Octree::Octree(const Maths::Vector3 & centre, float sideLength)
	: centre(centre), sideLength(sideLength), 
	boundingBox(Maths::Vector3(-sideLength / 2.0f, -sideLength / 2.0f, -sideLength / 2.0f),
				Maths::Vector3(sideLength / 2.0f, sideLength / 2.0f, sideLength / 2.0f),
				centre),
	nodeDepth(0),
	meshes()

{
	// Set the nodes to empty
	for (int i = 0; i < 8; i++)
		nodes[i] = 0;
}

#pragma region Private Constructors

Octree::Octree(unsigned int nodeDepth, const Maths::Vector3 & centre, float sideLength)
	: nodeDepth (nodeDepth), centre(centre), sideLength(sideLength),
	boundingBox(Maths::Vector3(-sideLength / 2.0f, -sideLength / 2.0f, -sideLength / 2.0f),
				Maths::Vector3(sideLength / 2.0f, sideLength / 2.0f, sideLength / 2.0f),
				centre),
	meshes()
{
	// Set the nodes to empty
	for (int i = 0; i < 8; i++)
		nodes[i] = 0;
}

#pragma endregion

Octree::~Octree(void)
{
	// Delete the node content if it exists
	for (int i = 0; i < 8; i++)
	{
		if (nodes[i])
			delete nodes[i];
	}
}

#pragma endregion

#pragma region Octree Routines

void Octree::AddMesh(Model::MeshAlias * mesh)
{
	if (this->nodeDepth == maxRecursionDepth)
	{
		// Insert the mesh into this node as it is a leaf
		meshes.insert(mesh);

		// Return as no more nodes should be created
		return;
	}

	// Check whether the mesh's bounding box falls inside this bounding box
	IntersectResult result = this->boundingBox.Intersects(mesh->GetBoundingVolume());

	//float meshVolume = mesh->GetBoundingVolume()->GetVolume();
	//float boxVolume = this->boundingBox.GetVolume();

	switch (result)
	{
	case NO_OVERLAP:
		return;

	case INTERSECTS:

		// DO A TEST TO CHECK IF THE BOUNDING BOX IS SMALLER THAN THE CURRENT NODE'S,
		// AND IF SO KEEP RECURSING

		if ((mesh->GetBoundingVolume()->GetVolume()) < (this->boundingBox.GetVolume()))
		{
			// Ensure the child nodes exist
			CreateAllNodes();

			// Loop over the child nodes and recursively add the model 
			for (int i = 0; i < 8; ++i)
			{
				nodes[i]->AddMesh(mesh);
			}
		}
		else
		{
			// If there is an intersection, but not full containment, add to this node
			meshes.insert(mesh);
		}

		break;

	case CONTAINS:

		// Ensure the child nodes exist
		CreateAllNodes();

		// Loop over the child nodes and recursively add the model 
		for (int i = 0; i < 8; ++i)
		{
			nodes[i]->AddMesh(mesh);
		}

		break;
	}

}

std::set<Model::MeshAlias *> Octree::GetVisibleMeshes(const BoundingFrustum & bf) const
{
	// Create a set to put visible meshes in
	std::set<Model::MeshAlias *> visibleMeshes;

	std::set<Model::MeshAlias *> childMeshes;

	IntersectResult result = bf.Intersects(this->boundingBox);

	switch (result)
	{
	case CONTAINS:

		// If the frustum contains this node, get all the nodes from this
		// and its children
		return this->GetAllMeshes();

	case INTERSECTS:

		// If there is an intersection, insert this level's meshes into the 
		// return placeholder, then recurse over child nodes
		visibleMeshes.insert(meshes.begin(), meshes.end());

		// Loop over the nodes
		for (int i = 0; i < 8; ++i)
		{
			// If the node exists
			if (nodes[i])
			{
				// Recurse with the frustum to check intersection on child nodes
				childMeshes = nodes[i]->GetVisibleMeshes(bf);
				// Put them into the visible meshes set
				visibleMeshes.insert(childMeshes.begin(), childMeshes.end());
				// Clear the placeholder
				childMeshes.clear();
			}
		}

		break;
	case NO_OVERLAP:
		break;
	}

	return visibleMeshes;
}

std::set<Model::MeshAlias *> Octree::GetAllMeshes() const
{
	// Create a set for all the meshes in this and deeper nodes
	std::set<Model::MeshAlias *> allMeshes;

	// Create a placeholder set for child nodes
	std::set<Model::MeshAlias *> childMeshes;

	// Put all of the meshes at this level into the set using iterators
	allMeshes.insert(meshes.begin(), meshes.end());

	// Loop over the node pointers
	for (int i = 0; i < 8; ++i)
	{
		// If there is a node present
		if (nodes[i])
		{
			// Get the child node's meshes
			childMeshes = nodes[i]->GetAllMeshes();

			// Insert them into this node's mesh set using iterators
			allMeshes.insert(childMeshes.begin(), childMeshes.end());

			// Clear the placeholder set
			childMeshes.clear();
		}
	}

	return allMeshes;
}

void Octree::CreateNode(int index)
{
	// Bounds checking
    if (index < 0 || index > 7)
        return;

	// Check if the node already exists
	if (nodes[index] != 0)
		return;

	Maths::Vector3 nodeCentre(this->centre);

	switch (index)
	{
	case FRONT_TOP_LEFT:

		nodeCentre.x += -(this->sideLength / 4.0f);
		nodeCentre.y += this->sideLength / 4.0f;
		nodeCentre.z += this->sideLength / 4.0f;

		break;

	case FRONT_TOP_RIGHT:

		nodeCentre.x += this->sideLength / 4.0f;
		nodeCentre.y += this->sideLength / 4.0f;
		nodeCentre.z += this->sideLength / 4.0f;

		break;

	case FRONT_BOTTOM_LEFT:

		nodeCentre.x += -(this->sideLength / 4.0f);
		nodeCentre.y += -(this->sideLength / 4.0f);
		nodeCentre.z += this->sideLength / 4.0f;
		
		break;

	case FRONT_BOTTOM_RIGHT:

		nodeCentre.x += this->sideLength / 4.0f;
		nodeCentre.y += -(this->sideLength / 4.0f);
		nodeCentre.z += this->sideLength / 4.0f;

		break;

	case BACK_TOP_LEFT:

		nodeCentre.x += -(this->sideLength / 4.0f);
		nodeCentre.y += this->sideLength / 4.0f;
		nodeCentre.z += -(this->sideLength / 4.0f);

		break;

	case BACK_TOP_RIGHT:

		nodeCentre.x += this->sideLength / 4.0f;
		nodeCentre.y += this->sideLength / 4.0f;
		nodeCentre.z += -(this->sideLength / 4.0f);

		break;

	case BACK_BOTTOM_LEFT:

		nodeCentre.x += -(this->sideLength / 4.0f);
		nodeCentre.y += -(this->sideLength / 4.0f);
		nodeCentre.z += -(this->sideLength / 4.0f);

		break;

	case BACK_BOTTOM_RIGHT:

		nodeCentre.x += this->sideLength / 4.0f;
		nodeCentre.y += -(this->sideLength / 4.0f);
		nodeCentre.z += -(this->sideLength / 4.0f);

		break;
	}

	nodes[index] = new Octree(this->nodeDepth + 1, nodeCentre, this->sideLength / 2.0f);
}

void Octree::CreateAllNodes()
{
	for (int i = 0; i < 8; ++i)
	{
		CreateNode(i);
	}
}

#pragma endregion