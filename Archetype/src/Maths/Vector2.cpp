
#include "StdAfx.h" 

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