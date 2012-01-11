//
//  Matrix3x3.cpp
//  Archetype
//
//  Created by Jay Steen on 09/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector3.h"

using namespace AT;
using namespace Maths;

void Matrix3x3::Init(float m00, float m01, float m02,
                     float m10, float m11, float m12,
                     float m20, float m21, float m22)
{
    matrix[0] = m00; matrix[3] = m01; matrix[6] = m02;
    matrix[1] = m10; matrix[4] = m11; matrix[7] = m12;
    matrix[2] = m20; matrix[5] = m21; matrix[8] = m22;
}

Matrix3x3::Matrix3x3()
{
    Init(1, 0, 0, 
         0, 1, 0, 
         0, 0, 1);
}

Matrix3x3::Matrix3x3(float m00, float m01, float m02,
                     float m10, float m11, float m12,
                     float m20, float m21, float m22)
{
    Init(m00, m01, m02, 
         m10, m11, m12, 
         m20, m21, m22);
}

Matrix3x3::Matrix3x3(float m[9])
{
    // Loop n' copy
    for (int i = 0; i < 9; ++i)
    {
        matrix[i] = m[i];
    }
}

Matrix3x3::Matrix3x3(const Matrix4x4 & m)
{
    Init(m.GetValue(0, 0), m.GetValue(0, 1), m.GetValue(0, 2), 
         m.GetValue(1, 0), m.GetValue(1, 1), m.GetValue(1, 2), 
         m.GetValue(2, 0), m.GetValue(2, 1), m.GetValue(2, 2));
}

Matrix3x3::Matrix3x3(const Vector3 & row0, const Vector3 & row1, const Vector3 & row2, bool transpose)
{
    if (transpose)
    {
        Init(row0.x, row1.x, row2.x, 
             row0.y, row1.y, row2.y, 
             row0.z, row1.z, row2.z);
    }
    else
    {
        Init(row0.x, row0.y, row0.z, 
             row1.x, row1.y, row1.z, 
             row2.x, row2.y, row2.z);
    }
}

#pragma region Getters and Setters

float Matrix3x3::GetValue(int row, int column) const
{
    // Prevent out of bounds access
    if (row < 0 || row > 2 || column < 0 || column > 2)
        throw "Array out of bounds.";
    
    // Columns begin on 0, 3, 6
    return matrix[column * 3 + row];
}

float Matrix3x3::GetDeterminant() const
{
    // From p.126 of 3D Math Primer for Graphics and Game Development
    
    return matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5])
        + matrix[3] * (matrix[7] * matrix[2] - matrix[1] * matrix[8])
        + matrix[6] * (matrix[1] * matrix[5] - matrix[4] * matrix[2]);
}

const float * Matrix3x3::GetArray() const
{
    return matrix;
}

Vector3 Matrix3x3::operator* (const Vector3 & v) const
{
    return Vector3(matrix[0] * v.x + matrix[3] * v.y + matrix[6] * v.z,
                   matrix[1] * v.x + matrix[4] * v.y + matrix[7] * v.z,
                   matrix[2] * v.x + matrix[5] * v.y + matrix[8] * v.z);
}

#pragma endregion

Matrix3x3 Matrix3x3::CreateMinorOf(const Matrix4x4 & m, int row, int column)
{
    // Prevent out of bounds errors
    if (row > 3) row = 3;
    if (row < 0) row = 0;
    if (column > 3) column = 3;
    if (column < 0) column = 0;
    
    // Declare a float array that is compatible with the loop
    float minor[9];
    
    // Loop over the rows of the matrix, avoiding copying those which have been deleted 
    for (int i = 0, rowCount = 0; i < 4; ++i)
    {
        // If the row looper isn't the row to delete
        if (i != row)
        {
            // Loop over the columns
            for (int j = 0, columnCount = 0; j < 4; ++j)
            {
                // If the column looper isn't the one to delete
                if (j != column)
                {
                    // Copy the value from the matrix passed in
                    minor[columnCount * 3 + rowCount] = m.GetValue(i, j);
                    // Increment the column count
                    ++columnCount;
                }
            }
            
            // Increment the row count
            ++rowCount;
        }
    }
    
    // Return a nice new 3x3 matrix that is the minor of that passed in
    return Matrix3x3(minor);
}