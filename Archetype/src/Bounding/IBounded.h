//
//  IBounded.h
//  Archetype
//
//  Created by Jay Steen on 20/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
//  An interface that allows objects of varying types to be contained within
//  the same octree, as long as they implement a getter of a bounding volume

#pragma once

#include "libPrefix.h"
#include "BoundingVolume.h"

namespace AT 
{

namespace Bounding
{
    
class IBounded 
{
    
public:
    
    DLLEXPORT IBounded();
    
    DLLEXPORT virtual ~IBounded();
    
    DLLEXPORT virtual BoundingVolume * GetBoundingVolume() const = 0;
    
    DLLEXPORT virtual void SetBoundingVolume(const BoundingVolume & bv);
    
};    
        
}
}