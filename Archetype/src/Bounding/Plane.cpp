 
#include "StdAfx.h" 

#include "Plane.h"

using namespace AT;
using namespace Bounding;

Plane::Plane(const Maths::Vector3 & position, const Maths::Vector3 & normal)
	: normal(normal), d( -(Maths::Vector3::Dot(this->normal, position)))
{
	this->NormalisePlane();
}

Plane::Plane(float planeConstant, const Maths::Vector3 & normal)
	: normal(normal), d(planeConstant)
{
	this->NormalisePlane();
}

void Plane::NormalisePlane()
{
	float normalMag = this->normal.Length();

	normal /= normalMag;
	d /= normalMag;
}

float Plane::DistanceToPlane(const Maths::Vector3 & point) const
{
	// Get the distance to the point from the plane
	float distanceToPlane = normal.x * point.x + 
		normal.y * point.y + 
		normal.z * point.z +
		this->d;

	return distanceToPlane;
}

Halfspace Plane::CheckHalfspace(const Maths::Vector3 & point) const
{
	float distanceToPlane = this->DistanceToPlane(point);

	if (distanceToPlane > 0.0)
		return POSITIVE;
	else if (distanceToPlane < 0.0)
		return NEGATIVE;
	else 
		return ON_PLANE;
}

std::ostream & AT::Bounding::operator<< (std::ostream & o, const Plane & plane)
{
	o << "< a(" << plane.GetNormal().x << ") + b(" 
		<< plane.GetNormal().y << ") + c("
		<< plane.GetNormal().z << ") + d("
		<< plane.GetD() << ") = 0 >";

	// Return the ostream for chaining
	return o;
}