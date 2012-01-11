#pragma once

#include "libPrefix.h"

#include "Vector3.h"

namespace AT
{
namespace Bounding
{

class Ray
{
	// Position of the origin of the ray
	Maths::Vector3 origin;

	// The direction of the ray (normalised on construction)
	Maths::Vector3 direction;

	// The length of the ray. Zero or negative
	// length defines an infinite ray
	float length;


public:

	DLLEXPORT Ray(const Maths::Vector3 & origin = Maths::Vector3(), const Maths::Vector3 & direction = Maths::Vector3(0,0,-1), float length = 0);

	DLLEXPORT ~Ray(void);

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetOrigin() const;

	DLLEXPORT const Maths::Vector3 & GetDirection() const;

	DLLEXPORT float GetLength() const;

#pragma endregion

};

}
}