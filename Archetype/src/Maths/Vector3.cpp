 
#include "StdAfx.h" 

#include "Vector3.h"
#include "Vector4.h"
#include "SharedFunctions.h"
#include <cmath>


using namespace AT;
using namespace Maths;

#pragma region Constructors

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector4 & v) : x(v.x), y(v.y), z(v.z)
{
}


#pragma endregion

#pragma region Destructors

Vector3::~Vector3()
{
}

#pragma endregion

#pragma region Overloaded Operators

Vector3 Vector3::operator- () const
{
	return Vector3(-x, -y, -z);
}

void Vector3::operator*= (float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3::operator/= (float scale)
{
	// Divide each component by the scalar
	x /= scale;
	y /= scale;
	z /= scale;
}

void Vector3::operator+=(const Vector3& v)
{
	// Add each component of the R-variable vector to this object
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator-= (const Vector3& v)
{
	*this += -v;
}

#pragma endregion

#pragma region Member Functions

void Vector3::Normalise()
{
	// Compute the length of the vector
	float length = this->Length();

	// Divide each component by the length
	/*x /= length;
	y /= length;
	z /= length;*/

	*this /= length;
}

float Vector3::Length() const
{
	// Returns the square root of the length squared (ie the length)
	return sqrt(this->LengthSquared());
}

float Vector3::LengthSquared() const
{
	// Squares each component and returns the sum
	return x*x + y*y + z*z;
}

#pragma endregion

#pragma region Class Functions

float Vector3::Dot(const Vector3 & v1, const Vector3 & v2)
{
	return v1.x * v2.x 
		 + v1.y * v2.y 
		 + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y,
				   v1.z * v2.x - v1.x * v2.z,
				   v1.x * v2.y - v1.y * v2.x);
}

#pragma endregion

#pragma region Non-Member Operator Overloads

namespace AT
{
namespace Maths
{
	Vector3 operator* (const Vector3 & v, float scale)
	{
		// Returns a vector multiplied by the scale factor
		return Vector3(v.x * scale, v.y * scale, v.z * scale);
	}

	Vector3 operator/ (const Vector3 & v, float scale)
	{
		// Returns a vector divided by the scale factor
		return Vector3(v.x / scale, v.y / scale, v.z / scale);
	}

	Vector3 operator+ (const Vector3 & a, const Vector3 & b)
	{
		// Returns two vectors added together
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Vector3 operator- (const Vector3 & a, const Vector3 & b)
	{
		// Returns a vector with all the components subtracted piecewise
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	std::ostream & operator<< (std::ostream & o, const Vector3 & v)
	{
		// Output the vector in the form (x,y,z)
		o << "(" << ZeroSmallFloat(v.x) << ", " << ZeroSmallFloat(v.y) << ", " << ZeroSmallFloat(v.z) << ")";

		// Return the output stream for chaining
		return o;
	}
}
}

#pragma endregion

#pragma region Factory Methods

Vector3 Vector3::Zero()
{
	return Vector3(0,0,0);
}
	
Vector3 Vector3::Up()
{
	return Vector3(0,1,0);
}

Vector3 Vector3::Right()
{
	return Vector3(1,0,0);
}

Vector3 Vector3::Forward()
{
	return Vector3(0,0,-1);
}

#pragma endregion