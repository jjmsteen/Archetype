 
#include "stdafx.h" 

#include "Light2.h"

#include "GeometryFactory.h"
/*
using namespace AT;

Light2::Light2(const std::string & name, LightType lightType, bool isEmitting, 
	const Maths::Matrix4x4 & worldTransform, const Model::Colour & diffuseColour,
	float range, float exponent, float coneSize, unsigned int detail)
	: Emitter(name, worldTransform, isEmitting), lightType(lightType), diffuseColour(diffuseColour)
{
	switch (lightType)
	{
	case SPOT_LIGHT:

		emitterShape = Model::GeometryFactory::Cone(range, coneSize, detail);

		break;

	case POINT_LIGHT:

		emitterShape = Model::GeometryFactory::Sphere(range, detail, detail);

		break;

	default:

		break;
	};
}


Light2::~Light2(void)
{
}

void Light2::Enable()
{
	emitting = true;
}

void Light2::Disable()
{
	emitting = false;
}

void Light2::Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader)
{
	if (emitterShape)
		emitterShape->Draw(worldTransform, View, Projection, shader);
}
*/