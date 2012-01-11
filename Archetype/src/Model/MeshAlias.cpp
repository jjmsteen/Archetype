//
//  MeshAlias.cpp
//  Archetype
//
//  Created by Jay Steen on 20/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "MeshAlias.h"

#include "BoundingAABB.h"
#include "BoundingSphere.h"

using namespace AT; using namespace Model;

MeshAlias::MeshAlias(Mesh & mesh)
:   sourceMesh(&mesh), 
    boundingVolume(mesh.GetBoundingVolume()->Copy()),
    worldMatrix(mesh.GetWorldMatrix())
{
    
}

Bounding::BoundingVolume * MeshAlias::GetBoundingVolume() const
{
    return this->boundingVolume;
}

const Maths::Matrix4x4 & MeshAlias::GetWorldMatrix() const
{
    return worldMatrix;
}

void MeshAlias::SetWorldMatrix(const Maths::Matrix4x4 & m)
{
    this->worldMatrix = m;
    
    switch (this->boundingVolume->GetBoundingType()) 
    {
        case Bounding::BoundingVolume::BOUNDING_AABB:
            
            ((Bounding::BoundingAABB*)this->boundingVolume)->transform = m.GetTranslation();
            
            break;
            
        case Bounding::BoundingVolume::BOUNDING_SPHERE:
            
            ((Bounding::BoundingSphere*)this->boundingVolume)->SetCentre(m.GetTranslation());
            
            break;
            
        default:
            break;
    }
}

const Material * MeshAlias::GetMaterial() const
{
    return this->sourceMesh->GetMaterial();
}

void MeshAlias::Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader)
{
    sourceMesh->Draw(this->worldMatrix, View, Projection, shader);
}