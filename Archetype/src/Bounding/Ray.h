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
	Maths::Vector3 mOrigin;

	// The end of the ray
	Maths::Vector3 mEnd;


public:

	DLLEXPORT Ray(const Maths::Vector3 & lOrigin = Maths::Vector3(), const Maths::Vector3 & lEnd = Maths::Vector3(0,0,-1));

	DLLEXPORT ~Ray(void);

#pragma region Getters and Setters

	DLLEXPORT Maths::Vector3 GetRayVector() const;

	DLLEXPORT const Maths::Vector3 & GetOrigin() const { return mOrigin; }

	DLLEXPORT const Maths::Vector3 & GetEnd() const { return mEnd; }

	DLLEXPORT Maths::Vector3 GetDirection() const;

	DLLEXPORT float GetLength() const;

#pragma endregion

};

}
}