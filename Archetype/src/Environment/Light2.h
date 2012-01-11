#pragma once

#include "libPrefix.h"

#include <string>

#include "Emitter.h"
#include "Colour.h"
/*
namespace AT
{

typedef enum {

	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT

} LightType;


class Light2 : public Emitter
{
protected:

	LightType lightType;

	Model::Colour diffuseColour; 

public:

	DLLEXPORT Light2(const std::string & name, LightType lightType, bool isEmitting, 
		const Maths::Matrix4x4 & worldTransform, const Model::Colour & diffuseColour, 
		float range = 100.0f, float exponent = 1.0f, float coneSize = 20.0f, unsigned int detail = 5);
	 
	DLLEXPORT virtual ~Light2(void);

#pragma region Enable Disable Methods

	DLLEXPORT virtual void Enable();

	DLLEXPORT virtual void Disable();

#pragma endregion

#pragma region Drawing Routines

	DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader);

#pragma endregion
};

}
*/