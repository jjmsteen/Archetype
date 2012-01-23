 #include "stdafx.h" 

#include <cmath>

#include "BoundingFrustum.h"
#include "Plane.h"
#include "Vector3.h"

#include "BoundingAABB.h"
#include "BoundingSphere.h"

using namespace AT;
using namespace Bounding;

// Values for these planes sourced from "Fast Extraction of Viewing 
// Frustum Planes from the WorldView-Projection Matrix" by Gribb and Hartmann
BoundingFrustum::BoundingFrustum(const Maths::Matrix4x4 & frustum)
	: left(frustum.GetValue(3,3) + frustum.GetValue(0,3), 
		Maths::Vector3(frustum.GetValue(3,0) + frustum.GetValue(0,0),
					   frustum.GetValue(3,1) + frustum.GetValue(0,1),
					   frustum.GetValue(3,2) + frustum.GetValue(0,2))),

	right(frustum.GetValue(3,3) - frustum.GetValue(0,3), 
		Maths::Vector3(frustum.GetValue(3,0) - frustum.GetValue(0,0),
					   frustum.GetValue(3,1) - frustum.GetValue(0,1),
					   frustum.GetValue(3,2) - frustum.GetValue(0,2))),

	top(frustum.GetValue(3,3) - frustum.GetValue(1,3), 
		Maths::Vector3(frustum.GetValue(3,0) - frustum.GetValue(1,0),
					   frustum.GetValue(3,1) - frustum.GetValue(1,1),
					   frustum.GetValue(3,2) - frustum.GetValue(1,2))),

	bottom(frustum.GetValue(3,3) + frustum.GetValue(1,3), 
		Maths::Vector3(frustum.GetValue(3,0) + frustum.GetValue(1,0),
					   frustum.GetValue(3,1) + frustum.GetValue(1,1),
					   frustum.GetValue(3,2) + frustum.GetValue(1,2))),

	zNear(frustum.GetValue(3,3) + frustum.GetValue(2,3), 
		Maths::Vector3(frustum.GetValue(3,0) + frustum.GetValue(2,0),
					   frustum.GetValue(3,1) + frustum.GetValue(2,1),
					   frustum.GetValue(3,2) + frustum.GetValue(2,2))),

	zFar(frustum.GetValue(3,3) - frustum.GetValue(2,3), 
		Maths::Vector3(frustum.GetValue(3,0) - frustum.GetValue(2,0),
					   frustum.GetValue(3,1) - frustum.GetValue(2,1),
					   frustum.GetValue(3,2) - frustum.GetValue(2,2)))
{
	PopulatePointerArray();
}


BoundingFrustum::~BoundingFrustum(void)
{
}

BoundingVolume * BoundingFrustum::Copy() const
{
    return new BoundingFrustum(*this);
}

BoundingFrustum::BoundingFrustum(const BoundingFrustum & bf)
	: left(bf.left), right(bf.right), top(bf.top), bottom(bf.bottom),
	zNear(bf.zNear), zFar(bf.zFar)
{
	PopulatePointerArray();
}

BoundingFrustum & BoundingFrustum::operator= (const BoundingFrustum & bf)
{
	left = bf.left; 
	right = bf.right; 
	top = bf.top; 
	bottom = bf.bottom;
	zNear = bf.zNear; 
	zFar = bf.zFar;

	PopulatePointerArray();

	return *this;
}

void BoundingFrustum::PopulatePointerArray()
{
	planes[0] = &left;
	planes[1] = &right;
	planes[2] = &top;
	planes[3] = &bottom;
	planes[4] = &zNear;
	planes[5] = &zFar;
}

float BoundingFrustum::GetVolume() const
{
	return 0.0f;
}

IntersectResult BoundingFrustum::Intersects(const BoundingVolume * bv)
{
	return BoundingVolume::Intersects(bv);
}

bool BoundingFrustum::DoesRayIntersect(const Ray & ray) const
{
	return false;
}

IntersectResult BoundingFrustum::Intersects(const BoundingAABB & box) const
{
	// Create results for the minimum and maximum box points
	//Halfspace minResult;
	//Halfspace maxResult;

	IntersectResult result;

	// Create a result counter (to add up plane test results)
	int resultCounter = 0;

	for (int i = 0; i < 6; i++)
	{
	//	// Test against the left plane
	//	minResult = planes[i]->CheckHalfspace(box.GetMin());
	//	maxResult = planes[i]->CheckHalfspace(box.GetMax());

		result = box.Intersects(*planes[i]);

		// Switch to evaluate results faster than if
		switch (result)
		{
			// If both results are negative (ie outside the box)
		case NO_OVERLAP:

			// Return the function as no overlap exists
			// Returns here to save processing time
			return NO_OVERLAP;

			// If both are positive (ie inside the box)
		case CONTAINS:

			// Add a containment count to the result
			resultCounter += CONTAINS;
			break;

			// If any other results occur (like half inside)
		default:

			// Add an intersection count to the result
			resultCounter += INTERSECTS;
			break;
		}
	}

	// Switch to evaluate the result counter quickly
	switch(resultCounter)
	{
		// If there has been a contain result on all 6 planes, 
		// return containment as result
	case CONTAINS * 6:
		return CONTAINS;

		// All other results indicate an intersection
	default:
		return INTERSECTS;
	}
}

IntersectResult BoundingFrustum::Intersects(const BoundingFrustum & frustum) const
{
	return NO_OVERLAP;
}

IntersectResult BoundingFrustum::Intersects(const BoundingSphere & sphere) const
{    
	// A halfspace test result for the centre of the sphere
	Halfspace centreResult;

	// A counter for the intersection results for each plane
	int resultCounter = 0;

	for (int i = 0; i < 6; i++)
	{
		// Get the distance from the sphere centre to the plane
		float distanceToPlane = planes[i]->DistanceToPlane(sphere.GetCentre());

		// If this distance is greater than the radius
		if (fabs(distanceToPlane) > sphere.GetRadius())
		{
			// Find out which side of the plane the centre of the sphere is on
			centreResult = planes[i]->CheckHalfspace(sphere.GetCentre());

			// Increment the result counter accordingly
			switch (centreResult)
			{
				// If the centre is inside or on the plane
            case ON_PLANE:
			case POSITIVE:
				// Add a contain to the result count
				resultCounter += CONTAINS;
				break;

				// If the centre is outside
			case NEGATIVE:

				// Return a no overlap to save time
				return NO_OVERLAP;
			}
		}
		else
		{
			// If the distance to the plane is less than the radius, it intersects
			resultCounter += INTERSECTS;
		}
	}

	switch (resultCounter)
	{
		// If the result is containment on all planes
	case CONTAINS * 6:
		return CONTAINS;

		// If there is no overlap
	case NO_OVERLAP:
		return NO_OVERLAP;

		// Any other results indicate an intersection
	default:
		return INTERSECTS;
	}
	
	
}

IntersectResult BoundingFrustum::Intersects(const Maths::Vector3 & point) const
{
	Halfspace hs;

	// Check which half space the point belongs to on the left plane
	hs = left.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	// Check which half space the point belongs to on the top plane
	hs = top.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	// Check which half space the point belongs to on the far plane
	hs = zFar.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	// Check which half space the point belongs to on the right plane
	hs = right.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	// Check which half space the point belongs to on the bottom plane
	hs = bottom.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	// Check which half space the point belongs to on the near plane
	hs = zNear.CheckHalfspace(point);

	// If it is in the negative halfspace, it can't be inside the frustum
	if (hs == NEGATIVE) return NO_OVERLAP;

	return CONTAINS;
}

DLLEXPORT IntersectResult BoundingFrustum::Intersects(const Plane & plane) const
{
	return NO_OVERLAP;
}