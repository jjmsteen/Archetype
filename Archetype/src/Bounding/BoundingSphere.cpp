#include "stdafx.h"
#include "BoundingSphere.h"
#include "SharedFunctions.h"

#include <cmath>

using namespace AT;
using namespace Bounding;
using namespace Maths;

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
	return (4.0f / 3.0f) * (float)AT::Maths::PI * radius * radius * radius;
}

Vector3 BoundingSphere::GetCentroid() const
{
	return GetCentre();
}

IntersectResult BoundingSphere::Intersects(const BoundingVolume * bv)
{
	return BoundingVolume::Intersects(bv);
}

bool BoundingSphere::DoesRayIntersect(const Ray & ray) const
{
	// Check if the origin or the end of the ray are inside the sphere first
	if ( (ray.GetOrigin() - centre).LengthSquared() < (radius * radius) ||
		 (ray.GetEnd() - centre).LengthSquared() < (radius * radius) )
	{
		return true;
	}

	// We're using the algorithm from 3D Maths primer for Graphics and Game Development
	// p 287-8.

	// e in the book
	Vector3 lOriginToCentre = centre - ray.GetOrigin();

	// a in the book
	float lfProjectedDistance = Vector3::Dot(lOriginToCentre, ray.GetDirection());

	// f squared in the book
	float lfRaySphereOverlapSq = (radius * radius) - lOriginToCentre.LengthSquared() 
		+ (lfProjectedDistance * lfProjectedDistance);

	if (lfRaySphereOverlapSq < 0.0f)
	{
		return false;
	}
	
	return true;
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