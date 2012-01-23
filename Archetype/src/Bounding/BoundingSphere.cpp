#include "stdafx.h"
#include "BoundingSphere.h"
#include "SharedFunctions.h"

#include <cmath>

using namespace AT;
using namespace Bounding;

BoundingSphere::BoundingSphere(const Maths::Vector3 & centre, float radius)
	: centre(centre), radius(fabs(radius))
{
}


BoundingSphere::~BoundingSphere(void)
{
}

BoundingVolume * BoundingSphere::Copy() const
{
    return new BoundingSphere(*this);
}

float BoundingSphere::GetVolume() const
{
	return (4.0f / 3.0f) * AT::Maths::PI * radius * radius * radius;
}

IntersectResult BoundingSphere::Intersects(const BoundingVolume * bv)
{
	return BoundingVolume::Intersects(bv);
}

bool BoundingSphere::DoesRayIntersect(const Ray & ray) const
{
	return false;
}

IntersectResult BoundingSphere::Intersects(const BoundingAABB & box) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingSphere::Intersects(const BoundingFrustum & frustum) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingSphere::Intersects(const BoundingSphere & sphere) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingSphere::Intersects(const Maths::Vector3 & point) const
{
	return NO_OVERLAP;
}

DLLEXPORT IntersectResult BoundingSphere::Intersects(const Plane & plane) const
{
	return NO_OVERLAP;
}