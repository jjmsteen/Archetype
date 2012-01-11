#pragma once

#include "libPrefix.h"

#include "Vector3.h"
#include <ostream>

// Based on the paper "Fast Extraction of Viewing Frustum Planes from the WorldView-Projection Matrix"
// by Gribb and Hartmann

// Representation of a plane as three components (a,b,c) and one constant (d).

// Planes are normally represented as n dot (x - p) = 0 where n is a normal vector, 
// p is a point on the plane and x is a set of all points on the plane

// This can be shown as (n dot x) - (n dot p) = 0

// -(n dot p) is a constant and so can be stored

// a,b,c are representative of the normal vector

namespace AT
{
namespace Bounding
{

// An enumeration of the possible halfspace states a point
// can be in
enum Halfspace
{
	NEGATIVE = -1,
	ON_PLANE = 0,
	POSITIVE = 1
};

class Plane
{
	// This is the normalised vector perpendicular to the plane
	Maths::Vector3 normal;

	// This is the constant -(n dot p)
	float d;

	DLLEXPORT void NormalisePlane();

public:

	// Allows a plane to be specified by the position and the normal, which defaults to the xz plane
	DLLEXPORT Plane(const Maths::Vector3 & position = Maths::Vector3(), const Maths::Vector3 & normal = Maths::Vector3(0,1,0));

	DLLEXPORT Plane(float planeConstant, const Maths::Vector3 & normal = Maths::Vector3(0,1,0));



#pragma region Getters

	DLLEXPORT const Maths::Vector3 & GetNormal() const { return normal;} 

	DLLEXPORT float GetD() const { return d; }

#pragma endregion

#pragma region Halfspace Checking Methods

	// Gets the signed distance of the point to its nearest point on the plane
	DLLEXPORT float DistanceToPlane(const Maths::Vector3 & point) const;

	// Gets the halfspace of the plane the point resides in
	DLLEXPORT Halfspace CheckHalfspace(const Maths::Vector3 & point) const;

#pragma endregion
};

#pragma region Non-Member Overloaded Operators

	DLLEXPORT std::ostream & operator<< (std::ostream & o, const Plane & plane);

#pragma endregion

}
}