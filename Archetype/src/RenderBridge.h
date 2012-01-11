#pragma once

// *** Class RENDER BRIDGE *** ///
// * * * * * * * * * * * * * * ///
// Provides an implementation  ///
// independent bridge class to ///
// decouple the mesh object    ///
// from its renderer		   ///
// * * * * * * * * * * * * * * ///

#include "libPrefix.h"

#include "VertexBuffer.h"
#include "ShaderEffect.h"
#include "Renderable.h"


namespace AT
{
namespace Model
{
    class Mesh;
}
    

class RenderBridge : public Renderable
{
public:

	Model::VertexBuffer * vertexBuffer;

	Model::ShaderEffect * shaderEffect;

public:

    DLLEXPORT RenderBridge();

	DLLEXPORT virtual ~RenderBridge(void);
    
    DLLEXPORT virtual void SetVertexBuffer(Model::VertexBuffer * vb);
    
    DLLEXPORT virtual void SetShaderEffect(Model::ShaderEffect * sh);

#pragma region Cloning methods

	DLLEXPORT virtual RenderBridge * CreateNewObject() const = 0;

	DLLEXPORT virtual RenderBridge * CloneThisObject() const = 0;

#pragma endregion
    
#pragma region Drawing
    
    DLLEXPORT virtual void Draw(const Model::Mesh & mesh, const Maths::Matrix4x4 & World, const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader) = 0;
    
#pragma endregion

};

}