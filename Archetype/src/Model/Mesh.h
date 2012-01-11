#pragma once

#include "libPrefix.h"

#include "Renderable.h"
#include "VertexBuffer.h"
#include "ShaderEffect.h"
#include "BoundingVolume.h"
#include "Material.h"
#include "RenderBridge.h"

#include <vector>
#include <string>


namespace AT
{
namespace Model
{

class Mesh :
	public Renderable
{

protected:

#pragma region Members

	// The name of the mesh
	std::string name;

	// A world matrix
	Maths::Matrix4x4 worldMatrix;

	// The vertex buffer holding the vertex data associated with
	// this mesh
	VertexBuffer vertexBuffer;

	// A weak pointer to the material for this mesh
	Material * material;

	// The renderer bridge object
	RenderBridge * renderer;

	// A bounding volume to enclose the mesh
	Bounding::BoundingVolume * boundingVolume;

#pragma endregion

public:

#pragma region Constructors

	//DLLEXPORT Mesh();

	DLLEXPORT Mesh(const std::string & name, const Maths::Matrix4x4 & worldTransform, 
		const VertexBuffer & vertexBuffer, Bounding::BoundingVolume * bv,
		Material * material = 0);

#pragma endregion

#pragma region Destructors

	DLLEXPORT ~Mesh();

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const std::string & GetName() { return name; }

	DLLEXPORT const Maths::Matrix4x4 & GetWorldMatrix() const { return worldMatrix; }
	DLLEXPORT void SetWorldMatrix(const Maths::Matrix4x4 & m) { worldMatrix = m; }

	DLLEXPORT void SetRenderer(RenderBridge * renderer);

	//DLLEXPORT void SetShader(ShaderEffect * effect, bool copy, bool deleteOld = true); 

	DLLEXPORT const Bounding::BoundingVolume * GetBoundingVolume() const { return boundingVolume; }
    
    DLLEXPORT const VertexBuffer & GetVertexBuffer() const { return vertexBuffer; }
    
    DLLEXPORT const Material * GetMaterial() const { return material; }
    
    DLLEXPORT const void SetMaterial(const Material& mat) { material = (Material*)&mat; }

#pragma endregion

#pragma region Methods

	DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & World, const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, ShaderEffect & shader);

#pragma endregion
};

}
}
