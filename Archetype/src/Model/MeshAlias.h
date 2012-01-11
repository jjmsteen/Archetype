//
//  MeshAlias.h
//  Archetype
//
//  Created by Jay Steen on 20/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
//  MeshAlias objects implement the Flyweight pattern for mesh objects. 
//  They allow many instances of the same mesh, without the duplication of large amounts of identical vertex data. 

#pragma once

#include "libPrefix.h"

#include "Mesh.h"
#include "IBounded.h"
#include "Renderable.h"
#include "BoundingVolume.h"

namespace AT 
{
    
namespace Model
{
    
class MeshAlias 
    : public Bounding::IBounded,
    public Renderable
{
    // Weak pointer to the mesh being instanced
    Mesh * sourceMesh;
    
    Bounding::BoundingVolume * boundingVolume;
    
    Maths::Matrix4x4 worldMatrix;
    
public:
    
    // Constructor only from a mesh object
    DLLEXPORT MeshAlias(Mesh & mesh);
    
#pragma region Getters and Setters
    
    // Implementation of IBounded interface
    DLLEXPORT virtual Bounding::BoundingVolume * GetBoundingVolume() const;
    
    DLLEXPORT const Maths::Matrix4x4 & GetWorldMatrix() const;
    DLLEXPORT void SetWorldMatrix(const Maths::Matrix4x4 & m);
    
    DLLEXPORT const Material * GetMaterial() const;
    
    
    
#pragma endregion
    
    // Overriding of Renderable interface method
    DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader);
};
        
}
}