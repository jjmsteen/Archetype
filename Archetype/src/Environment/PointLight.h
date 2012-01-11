//
//  PointLight.h
//  Archetype
//
//  Created by Jay Steen on 22/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "libPrefix.h"

#include "Light.h"
#include "Vector3.h"
#include "Colour.h"
#include "BoundingSphere.h"

namespace AT 
{
    
namespace Lighting
{

class PointLight 
    : public Light
{
    Bounding::BoundingVolume * boundingSphere;
    
    float radius;
    
    Maths::Vector3 centre;
    
    float specularLevel;
    
    float specularPower;
    
public:
    
    DLLEXPORT PointLight(const Model::Mesh & unitSphere, const Maths::Vector3 & centre, float radius, const Model::Colour & diffuseColour, float specularLevel, float specularPower);
    
    DLLEXPORT virtual void SetBoundingVolume(const Bounding::BoundingVolume &bv);
    
    DLLEXPORT virtual LightType GetLightType() const { return LIGHT_POINT; }
    
#pragma region Getters and Setters
    
    DLLEXPORT float GetRadius() const { return radius; }
    DLLEXPORT void SetRadius(float radius) { this->radius = radius; }
    
    DLLEXPORT const Maths::Vector3 & GetCentre() const { return centre; }
    DLLEXPORT void SetCentre(const Maths::Vector3 & centre) { this->centre = centre; }
    
    DLLEXPORT float GetSpecularLevel() const { return specularLevel; }
    DLLEXPORT void SetSpecularLevel(float specularLevel) { this->specularLevel = specularLevel; }
    
    DLLEXPORT float GetSpecularPower() const { return specularPower; }
    DLLEXPORT void SetSpecularPower(float specularPower) { this->specularPower = specularPower; }
    
#pragma endregion
    
    DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader);
    
};

}
}