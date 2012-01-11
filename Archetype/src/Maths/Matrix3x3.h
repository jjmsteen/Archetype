//
//  Matrix3x3.h
//  Archetype
//
//  Created by Jay Steen on 09/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "libPrefix.h"

namespace AT
{
namespace Maths
{
 
class Matrix4x4;
class Vector3;
    

class Matrix3x3 
{
    // The matrix representation in column major format
    float matrix[9];
    
    
    DLLEXPORT void Init(float m00, float m01, float m02,
                        float m10, float m11, float m12,
                        float m20, float m21, float m22);
    
public:
    
#pragma region Constructors and Destructor
    
    DLLEXPORT Matrix3x3();
    
    DLLEXPORT Matrix3x3(float m00, float m01, float m02,
                        float m10, float m11, float m12,
                        float m20, float m21, float m22);
    
    DLLEXPORT Matrix3x3(float m[9]);
    
    DLLEXPORT Matrix3x3(const Matrix4x4 & m);
    
    DLLEXPORT Matrix3x3(const Vector3 & row0, const Vector3 & row1, const Vector3 & row2, bool transpose = false);
    
#pragma endregion
    
#pragma region Getters and Setters
    
    DLLEXPORT float GetValue(int row, int column) const;
    
    DLLEXPORT float GetDeterminant() const;
    
    DLLEXPORT const float * GetArray() const;
    
#pragma endregion
    
#pragma region Overloaded Operators
    
    DLLEXPORT Vector3 operator* (const Vector3 & v) const;
    
#pragma endregion
    
#pragma region Class Methods
    
    DLLEXPORT static Matrix3x3 CreateMinorOf(const Matrix4x4 & m, int row, int column);
    
#pragma endregion
    
};

}
}