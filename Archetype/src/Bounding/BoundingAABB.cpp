#include "stdafx.h"
#include "BoundingAABB.h"
#include "Plane.h"

#include <cmath>

using namespace AT;
using namespace Bounding;

BoundingAABB::BoundingAABB(const Maths::Vector3 & minPoint, 
		const Maths::Vector3 & maxPoint, const Maths::Vector3 & transform)
		: minPoint(minPoint), maxPoint(maxPoint), transform(transform)
{
}


BoundingAABB::~BoundingAABB(void)
{
}

BoundingVolume * BoundingAABB::Copy() const
{
    return new BoundingAABB(*this);
}

float BoundingAABB::GetVolume() const
{
	float width = maxPoint.x - minPoint.x;
	float height = maxPoint.y - minPoint.y;
	float depth = maxPoint.z - minPoint.z;

	return width * depth * height;
}

IntersectResult BoundingAABB::Intersects(const BoundingVolume * bv)
{
	return BoundingVolume::Intersects(bv);
}

bool BoundingAABB::DoesRayIntersect(const Ray & ray) const
{
	return false;
}

IntersectResult BoundingAABB::Intersects(const BoundingAABB & box) const
{
	// From p765 of Real Time Rendering, 3rd Ed.
	//int resultCount = 0;

	// Check early if there is no overlap. If there is overlap, do more accurate testing
	if ((this->GetMin().x) > (box.GetMax().x) || (box.GetMin().x) > (this->GetMax().x))
		return NO_OVERLAP;
	if ((this->GetMin().y) > (box.GetMax().y) || (box.GetMin().y) > (this->GetMax().y))
		return NO_OVERLAP;
	if ((this->GetMin().z) > (box.GetMax().z) || (box.GetMin().z) > (this->GetMax().z))
		return NO_OVERLAP;

	// Check for containment

	if ((box.GetMin().x) > (this->GetMin().x) && (box.GetMax().x) < (this->GetMax().x)
		&& (box.GetMin().y) > (this->GetMin().y) && (box.GetMax().y) < (this->GetMax().y)
		&& (box.GetMin().z) > (this->GetMin().z) && (box.GetMax().z) < (this->GetMax().z))
		return CONTAINS;

	return INTERSECTS;

	//// If the box being tested's minimum x point is inside the volume
	//if ((box.GetMin().x) > (this->GetMin().x) || (box.GetMax().x) > (this->GetMin().x))
	//	resultCount++;

	//// If the box being tested's minimum y point is inside the volume
	//if ((box.GetMin().y) > (this->GetMin().y) || (box.GetMax().y) > (this->GetMin().y))
	//	resultCount++;

	//// If the box being tested's minimum z point is inside the volume
	//if ((box.GetMin().z) > (this->GetMin().z) || (box.GetMax().z) > (this->GetMin().z))
	//	resultCount++;

	//// If the box being tested's maximum x point is inside the volume
	//if ((box.GetMax().x) < (this->GetMax().x))
	//	resultCount++;

	//// If the box being tested's maximum y point is inside the volume
	//if ((box.GetMax().y) < (this->GetMax().y))
	//	resultCount++;

	//// If the box being tested's maximum z point is inside the volume
	//if ((box.GetMax().z) < (this->GetMax().z))
	//	resultCount++;

	// Switch statement for extra speed



	//switch (resultCount)
	//{
	//	// If all 6 tests pass, the testing box contains the tested box
	//case 6:
	//	return CONTAINS;

	//	// If no tests pass, the testing boxes are disjoint
	//case 0:
	//	return NO_OVERLAP;

	//	// Otherwise the tested box intersects the testing box
	//default:
	//	return INTERSECTS;
	//}
}

IntersectResult BoundingAABB::Intersects(const BoundingFrustum & frustum) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingAABB::Intersects(const BoundingSphere & sphere) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingAABB::Intersects(const Maths::Vector3 & point) const
{
    // If the point is in any dimension less than the minimum point
    if (point.x < (minPoint.x + transform.x)
        || point.y < (minPoint.y + transform.y)
        || point.z < (minPoint.z + transform.z))
        return NO_OVERLAP;
    
    // If the point is in any dimension more than the maximum point
    if (point.x > (maxPoint.x  + transform.x)
        || point.y > (maxPoint.y  + transform.y)
        || point.z > (maxPoint.z + transform.z))
        return NO_OVERLAP;
    
	return CONTAINS;
}

DLLEXPORT IntersectResult BoundingAABB::Intersects(const Plane & plane) const
{
	using namespace Maths;
	// From p755 in Real Time Rendering, 3rd ed.

	// Find the central point of the box
	Vector3 centre = ((this->GetMax()) + (this->GetMin())) / 2.0;

	// Get the positive half vector (that from the centre to the max point)
	Vector3 halfVector = (this->GetMax() - this->GetMin()) / 2.0;

	// Project the half vector on to the plane to find the extent
	float extent = (halfVector.x * fabs(plane.GetNormal().x)) +
		(halfVector.y * fabs(plane.GetNormal().y)) +
		(halfVector.z * fabs(plane.GetNormal().z));

	// Compute the signed distance, from the centre to the plane
	float signedDistance = plane.DistanceToPlane(centre);

	// In this case, no overlap means the whole volume is in the negative halfspace
	if (signedDistance - extent > 0.0) return CONTAINS;
	// Contains means the whole volume is in the positive halfspace
	if (signedDistance + extent < 0.0) return NO_OVERLAP;

	return INTERSECTS;
}