 
#include "stdafx.h"

#include "Ray.h"

using namespace AT;
using namespace Bounding;

Ray::Ray(const Maths::Vector3 & lOrigin, const Maths::Vector3 & lEnd)
	: mOrigin(lOrigin), mEnd(lEnd)
{
	mEnd.Normalise();
}


Ray::~Ray(void)
{
}

Maths::Vector3 Ray::GetRayVector() const
{
	return mEnd - mOrigin;
}

Maths::Vector3 Ray::GetDirection() const
{
	Maths::Vector3 lRayVector = GetRayVector();
	lRayVector.Normalise();
	return lRayVector;
}

float Ray::GetLength() const
{
	Maths::Vector3 lRayVector = GetRayVector();
	return lRayVector.Length();
}