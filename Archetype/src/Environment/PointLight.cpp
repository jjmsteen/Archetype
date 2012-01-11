//
//  PointLight.cpp
//  Archetype
//
//  Created by Jay Steen on 22/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "PointLight.h"
#include "MeshAlias.h"

using namespace AT; using namespace Lighting;

PointLight::PointLight(const Model::Mesh & unitSphere, const Maths::Vector3 & centre, float radius, const Model::Colour & diffuseColour, float specularLevel, float specularPower)
: Light(Model::MeshAlias((Model::Mesh&)unitSphere), diffuseColour), centre(centre), radius(radius), specularLevel(specularLevel), specularPower(specularPower)
{
    
    // Set the mesh alias' world matrix
    Light::lightShape.SetWorldMatrix(Maths::Matrix4x4::CreateTranslation(centre) *
                                     Maths::Matrix4x4::CreateScale(radius));
    
    // Set the bounding volume of this light based on the centre and radius
    this->SetBoundingVolume(Bounding::BoundingSphere(centre, radius));
}

void PointLight::SetBoundingVolume(const Bounding::BoundingVolume &bv)
{
    if (bv.GetBoundingType() == Bounding::BoundingVolume::BOUNDING_SPHERE)
    {
        boundingSphere = bv.Copy();
        
        Light::lightShape.SetBoundingVolume(*boundingSphere);
    }
}

void PointLight::Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader)
{
    Light::lightShape.Draw(View, Projection, shader);
}