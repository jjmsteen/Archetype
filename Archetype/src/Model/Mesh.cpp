 
#include "stdafx.h"


#include "Mesh.h"

using namespace AT;
using namespace Model;

Mesh::Mesh(const std::string & name, const Maths::Matrix4x4 & worldTransform, 
		const VertexBuffer & vertexBuffer,  Bounding::BoundingVolume * bv,
		Material * material)
		: name(name), worldMatrix(worldTransform),
		vertexBuffer(vertexBuffer), boundingVolume(bv), material(material), 
        renderer(0)
{
}


Mesh::~Mesh(void)
{
}

void Mesh::SetRenderer(RenderBridge * renderer)
{
	// Assign the renderer
	this->renderer = renderer;

	// Set the renderer values for rendering
	this->renderer->vertexBuffer = &this->vertexBuffer;
	//this->renderer->shaderEffect = this->shader;
}

void Mesh::Draw(const Maths::Matrix4x4 & World, const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, ShaderEffect & shader)
{
	if (renderer)
	{
        //shader.SetParameter("Model", worldMatrix);
        
        
		// Draw using the renderer bridge
		renderer->Draw(*this, shader);
	}
}

void Mesh::Draw(const Model::ShaderEffect & shader) 
{
	if (renderer)
	{
		// Draw using the renderer bridge
		renderer->Draw(*this, shader);
	}
}