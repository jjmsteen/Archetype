
#include "stdafx.h" 

#include "Vector2.h"
#include <cmath>

using namespace AT;
using namespace Maths;

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}


Vector2::~Vector2()
{
}

void Vector2::Normalise()
{
	float length = this->Length();

	x /= length;
	y /= length;
}

float Vector2::Length() const
{
	return sqrt(this->LengthSquared());
}

float Vector2::LengthSquared() const
{
	return x*x + y*y;
}

Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}

Vector2 AT::Maths::operator* (const Vector2 & v, float scale)
{
	return Vector2(v.x * scale, v.y * scale);
}

Vector2 AT::Maths::operator/ (const Vector2 & v, float scale)
{
	return Vector2(v.x / scale, v.y / scale);
}

Vector2 AT::Maths::operator+ (const Vector2 & a, const Vector2 & b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 AT::Maths::operator- (const Vector2 & a, const Vector2 & b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}