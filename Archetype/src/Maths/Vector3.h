#pragma once
#include "vector.h"
#include "libPrefix.h"
#include <ostream>

namespace AT
{
namespace Maths
{

class Vector4;

class Vector3 :	public Vector
{
	

public:
	
#pragma region Members

	// Members are public as any values are valid
	float x, y, z;

#pragma endregion

#pragma region Constructors

	DLLEXPORT Vector3();

	// Constructor with the three vector components as floats
	DLLEXPORT Vector3(float x, float y, float z);
    
    // Constructor from a vector4 (discarding w)
    DLLEXPORT Vector3(const Vector4 & v);

#pragma endregion

#pragma region Destructor

	// Destructors
	DLLEXPORT ~Vector3();

#pragma endregion

#pragma region Overloaded Operators

	DLLEXPORT Vector3 operator- () const;

	DLLEXPORT void operator*= (float scale);

	DLLEXPORT void operator/= (float scale);

	DLLEXPORT void operator+= (const Vector3& v);

	DLLEXPORT void operator-= (const Vector3& v);

#pragma endregion

#pragma region Member Functions

	/*<summary>
	Converts the vector to unit length
	</summary>*/
	DLLEXPORT virtual void Normalise();

	/*<summary> 
	Returns the magnitude (length) of the vector 
	</summary>*/
	DLLEXPORT virtual float Length() const;

	// Returns the length squared of the vector
	DLLEXPORT virtual float LengthSquared() const;

#pragma endregion

#pragma region Class Functions

	//DLLEXPORT virtual std::string ToString();
	
	DLLEXPORT static float Dot(const Vector3 & v1, const Vector3 & v2);

	DLLEXPORT static Vector3 Cross(const Vector3 & v1, const Vector3 & v2);

#pragma endregion

#pragma region Factory Methods

	// Returns a vector with all components initialised to zero
	DLLEXPORT static Vector3 Zero();
	
	// Returns a standard up vector (0, 1, 0)
	DLLEXPORT static Vector3 Up();

	// Returns a standard right vector (1, 0, 0)
	DLLEXPORT static Vector3 Right();

	// Returns an Right-Handed coordinate space forward vector (0, 0, -1)
	DLLEXPORT static Vector3 Forward();

#pragma endregion

};

#pragma region Non-Member Operator Overloads

// Overloaded * for a vector and a scalar
DLLEXPORT Vector3 operator* (const Vector3 & v, float scale);

// Overloaded / for a vector and a scalar
DLLEXPORT Vector3 operator/ (const Vector3 & v, float scale);

// Overloaded + operator for two vectors
DLLEXPORT Vector3 operator+ (const Vector3 & a, const Vector3 & b);

// Overloaded - operator (does opposite of +)
DLLEXPORT Vector3 operator- (const Vector3 & a, const Vector3 & b);

// Overloaded << operator for debug output
DLLEXPORT std::ostream & operator<< (std::ostream & o, const Vector3 & v);

#pragma endregion

}
}
