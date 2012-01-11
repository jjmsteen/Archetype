//
//  Matrix2x2.h
//  Archetype
//
//  Created by Jay Steen on 18/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "libPrefix.h" 

namespace AT
{
namespace Maths
{
    
class Vector2;

class Matrix2x2
{
    // The matrix array
    float matrix[4];
    
    // Shared init function
    DLLEXPORT void Init(float m00, float m01,
                        float m10, float m11);
    
public:
    
    DLLEXPORT Matrix2x2(float m00 = 1.0f, float m01 = 0.0f,
                        float m10 = 0.0f, float m11 = 1.0f);
    
#pragma region Creation Methods
    
    DLLEXPORT static Matrix2x2 CreateScale(float scale);
    
    DLLEXPORT static Matrix2x2 CreateScale(float scaleX, float scaleY);
    
    DLLEXPORT static Matrix2x2 CreateRotation(float angleRads);
    
#pragma endregion
    
#pragma region Transformations
    
    DLLEXPORT Vector2 operator* (const Vector2 & v) const;
    
#pragma endregion
    
#pragma region Getters
    
    DLLEXPORT float GetValue(unsigned short row, unsigned short column) const;
    
#pragma endregion
};
    
#pragma region Non-Member Operator Overloads
    
    DLLEXPORT Matrix2x2 operator* (const Matrix2x2 & m1, const Matrix2x2 & m2);
    
#pragma endregion
    
}
}