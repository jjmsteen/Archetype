 
#include "stdafx.h"

#include "Ray.h"

using namespace AT;
using namespace Bounding;

Ray::Ray(const Maths::Vector3 & origin, const Maths::Vector3 & direction, float length)
	: origin(origin), direction(direction), length(length)
{
	this->direction.Normalise();
}


Ray::~Ray(void)
{
}

const Maths::Vector3 & Ray::GetOrigin() const
{
	return origin;
}

const Maths::Vector3 & Ray::GetDirection() const
{
	return direction;
}

float Ray::GetLength() const
{
	return length;
}