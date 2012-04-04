#pragma once
#include "vector.h"
#include "libPrefix.h"

namespace AT
{
namespace Maths
{

class Vector2 :	public Vector
{
public:

#pragma region Members

	// Members are public as any values are valid
	float x, y;

#pragma endregion

#pragma region Constructors

	DLLEXPORT Vector2();

	DLLEXPORT Vector2(float x, float y);

#pragma endregion

#pragma region Destructor

	DLLEXPORT ~Vector2();

#pragma endregion

#pragma region Member functions

	DLLEXPORT virtual void Normalise();

	DLLEXPORT virtual float Length() const;

	DLLEXPORT virtual float LengthSquared() const;

#pragma endregion

#pragma region Class Methods

	// Returns a Vector2 object with all components initialised to zero
	DLLEXPORT static Vector2 Zero();

#pragma endregion

};

#pragma region Non-Member Operator Overloads

// Overloaded * for a vector and a scalar
DLLEXPORT Vector2 operator* (const Vector2 & v, float scale);

// Overloaded / for a vector and a scalar
DLLEXPORT Vector2 operator/ (const Vector2 & v, float scale);

// Overloaded + operator for two vectors
DLLEXPORT Vector2 operator+ (const Vector2 & a, const Vector2 & b);

// Overloaded - operator (does opposite of +)
DLLEXPORT Vector2 operator- (const Vector2 & a, const Vector2 & b);

#pragma endregion

}
}