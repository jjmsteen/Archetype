//
//  Matrix2x2.cpp
//  Archetype
//
//  Created by Jay Steen on 18/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Matrix2x2.h"

#include "Vector2.h"

#include <cmath>

using namespace AT; using namespace Maths;

void Matrix2x2::Init(float m00, float m01,
                     float m10, float m11)
{
    matrix[0] = m00;
    matrix[1] = m10;
    matrix[2] = m01;
    matrix[3] = m11;
}

Matrix2x2::Matrix2x2(float m00, float m01,
                     float m10, float m11)
{
    Init(m00, m01, 
         m10, m11);
}

Matrix2x2 Matrix2x2::CreateScale(float scale)
{
    return Matrix2x2(scale, 0.0f,
                     0.0f, scale);
}

Matrix2x2 Matrix2x2::CreateScale(float scaleX, float scaleY)
{
    return Matrix2x2(scaleX, 0.0f,
                     0.0f, scaleY);
}

Matrix2x2 Matrix2x2::CreateRotation(float angleRads)
{
    return Matrix2x2(cosf(angleRads), -sinf(angleRads), 
                     sinf(angleRads), cosf(angleRads));
}

Vector2 Matrix2x2::operator* (const Vector2 & v) const
{
    return Vector2(matrix[0] * v.x + matrix[2] * v.y,
                   matrix[1] * v.x + matrix[3] * v.y);
}

float Matrix2x2::GetValue(unsigned short row, unsigned short column) const
{
    if(row > 1 || column > 1)
        throw "Accessor to Matrix2x2 out of bounds.";
    
    return matrix[column * 2 + row];
}

Matrix2x2 AT::Maths::operator* (const Matrix2x2 & m1, const Matrix2x2 & m2)
{
    return Matrix2x2(m1.GetValue(0,0) * m2.GetValue(0,0) + m1.GetValue(0,1) * m2.GetValue(1,0),
                     m1.GetValue(1,0) * m2.GetValue(0,0) + m1.GetValue(1,1) * m2.GetValue(1,0),
                     m1.GetValue(0,0) * m2.GetValue(0,1) + m1.GetValue(0,1) * m2.GetValue(1,1),
                     m1.GetValue(1,0) * m2.GetValue(0,1) + m1.GetValue(1,1) * m2.GetValue(1,1));
}