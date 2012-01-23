#pragma once

#include "libPrefix.h"
#include "Matrix4x4.h"
#include "ShaderEffect.h"

namespace AT
{

class Renderable
{

protected:

public:

#pragma region Constructors

	DLLEXPORT Renderable();

#pragma endregion

#pragma region Destructor

	DLLEXPORT virtual ~Renderable();

#pragma endregion

#pragma region Virtual Methods 

	// Adopters don't have to respond to these methods, but they can if necessary

	// Standard drawing
	DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection) {};

	// Drawing with pre-parameterised shader
	DLLEXPORT virtual void Draw(const Model::ShaderEffect & shader) {};
    
    // Drawing with shaders
    DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & World, const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader) {};
    
    // Drawing with shaders with embedded world matrix
    DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader) {};

	// Drawing for billboards
	DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, 
		const Maths::Vector3 & Up, const Maths::Vector3 & Right) {};

#pragma endregion

};

}
