//
//  Vector4.cpp
//  Archetype
//
//  Created by Jay Steen on 11/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Vector4.h"
#include "Vector3.h"
#include <cmath>

using namespace AT;
using namespace Maths;

Vector4::Vector4()
: x(0), y(0), z(0), w(0)
{}

Vector4::Vector4(float x, float y, float z, float w)
: x(x), y(y), z(z), w(w)
{}

Vector4::Vector4(const Vector3 & v, float w)
: x(v.x), y(v.y), z(v.z), w(w)
{
}

Vector4::~Vector4()
{
    
}

Vector4 Vector4::operator- () const
{
    return Vector4(-x, -y, -z, -w);
}

void Vector4::operator*= (float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    w *= scale;
}

void Vector4::operator/= (float scale)
{
    float invScale = 1.0 / scale;
    
    *this *= invScale;
}

void Vector4::operator+= (const Vector4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void Vector4::operator-= (const Vector4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void Vector4::Normalise()
{
    *this *= this->Length();
}

float Vector4::Length() const
{
    return sqrt(this->LengthSquared());
}

float Vector4::LengthSquared() const
{
    return x*x + y*y + z*z + w*w;
}

Vector4 AT::Maths::operator* (const Vector4 & v, float scale)
{
    return Vector4(v.x * scale, v.y * scale, v.z * scale, v.w * scale);
}


Vector4 AT::Maths::operator/ (const Vector4 & v, float scale)
{
    return Vector4(v.x / scale, v.y / scale, v.z / scale, v.w / scale);
}


Vector4 AT::Maths::operator+ (const Vector4 & a, const Vector4 & b)
{
    return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vector4 AT::Maths::operator- (const Vector4 & a, const Vector4 & b)
{
    return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}