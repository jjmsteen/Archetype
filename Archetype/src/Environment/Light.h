//
//  Light.h
//  Archetype
//
//  Created by Jay Steen on 21/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "libPrefix.h"

#include "IBounded.h"
#include "Renderable.h"
#include "MeshAlias.h"
#include "Colour.h"

namespace AT 
{
    
namespace Lighting
{
    
    enum LightType
    {
        LIGHT_POINT,
        LIGHT_SPOT,
        LIGHT_SHADOW
    };
    

class Light 
    : public Bounding::IBounded,
      public Renderable
{
    
protected:
    
    Model::MeshAlias lightShape;
    
    Model::Colour diffuseColour; 
    
public:
    
    bool emitting;
    
    DLLEXPORT Light(const Model::MeshAlias & lightShape, const Model::Colour & diffuseColour);
    
    DLLEXPORT virtual Bounding::BoundingVolume * GetBoundingVolume() const;
    
    DLLEXPORT virtual LightType GetLightType() const = 0;
    
    DLLEXPORT virtual const Model::Colour & GetDiffuseColour() const { return diffuseColour; }
    
        
};

}
}