//
//  Light.cpp
//  Archetype
//
//  Created by Jay Steen on 21/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Light.h"

using namespace AT; using namespace Lighting;

Light::Light(const Model::MeshAlias & lightShape, const Model::Colour & diffuseColour)
: lightShape(lightShape), diffuseColour(diffuseColour)
{
}

Bounding::BoundingVolume * Light::GetBoundingVolume() const
{
    return lightShape.GetBoundingVolume();
}