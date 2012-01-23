 
#include "stdafx.h" 

#include "BoundingVolume.h"
#include <typeinfo>

using namespace AT;
using namespace Bounding;

BoundingVolume::BoundingVolume()
{
}


BoundingVolume::~BoundingVolume(void)
{
}

IntersectResult BoundingVolume::Intersects(const BoundingVolume * bv) const
{
	switch (bv->GetBoundingType())
	{
		// If the type returned is an AABB
	case BOUNDING_AABB:
		// Cast the bv pointer to an AABB pointer and evaluate
		return this->Intersects(*((BoundingAABB*)bv));

	case BOUNDING_SPHERE:
		return this->Intersects(*((BoundingSphere*)bv));

	case BOUNDING_FRUSTUM:
		return this->Intersects(*((BoundingFrustum*)bv));

	default:
		return NO_OVERLAP;
	}
}