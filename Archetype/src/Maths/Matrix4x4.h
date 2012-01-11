#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "libPrefix.h"

#include <ostream>

namespace AT
{
namespace Maths
{

class Matrix4x4
{

private:

#pragma region Members

	//float matrix[4][4];
    
    float matrix[16];

#pragma endregion

public:

#pragma region Constructors

	// Create a default identity matrix
	DLLEXPORT Matrix4x4();

	// Create a matrix from axis scale values
	DLLEXPORT Matrix4x4(float scaleX, float scaleY, float scaleZ);

	// Create a uniform scale matrix
	DLLEXPORT Matrix4x4(float scale);

	// Create a matrix from a translation
	DLLEXPORT Matrix4x4(const Vector3 & translation);

	// Create a matrix from a rotation (in radians) around an arbitrary axis
	DLLEXPORT Matrix4x4(const Vector3 & axis, double angle);

	// Create a matrix from an array of floats
	DLLEXPORT Matrix4x4(float matrix[16]);

	// Create a matrix by specifying each component individually
	DLLEXPORT Matrix4x4(float m00, float m01, float m02, float m03,
		      float m10, float m11, float m12, float m13,
			  float m20, float m21, float m22, float m23,
			  float m30, float m31, float m32, float m33);

#pragma region Private Constructors

private:

	// Create a lookat matrix with an eye position, a focus position (lookat point) and up vector
	DLLEXPORT Matrix4x4(const Vector3 & eyePosition, const Vector3 & focusPosition, const Vector3 & up);

	// Create a perspective matrix
	DLLEXPORT Matrix4x4(float fovY, float aspectRatio, float zNear, float zFar);

	// Create a frustum matrix
	DLLEXPORT Matrix4x4(float left, float right, float bottom, float top, float zNear, float zFar);

	// Create an orthographic projection matrix
	DLLEXPORT Matrix4x4(float width, float height, float zNear, float zFar, void * orthoMarker);

public:

#pragma endregion

#pragma endregion

#pragma region Static Factory Methods

	DLLEXPORT static Matrix4x4 CreateScale(float scaleX, float scaleY, float scaleZ);

	DLLEXPORT static Matrix4x4 CreateScale(float scale);

	DLLEXPORT static Matrix4x4 CreateRotation(const Vector3 & axis, double angleRadians);
    
    DLLEXPORT static Matrix4x4 CreateRotation(float yawRadians, float pitchRadians, float rollRadians);

	DLLEXPORT static Matrix4x4 CreateTranslation(const Vector3 & translation);

	DLLEXPORT static Matrix4x4 CreateLookAt(const Vector3 & eyePosition, const Vector3 & focusPosition, const Vector3 & up);

	DLLEXPORT static Matrix4x4 CreatePerspective(float fovY, float aspectRatio, float zNear, float zFar);

	DLLEXPORT static Matrix4x4 CreateFrustum(float left, float right, float bottom, float top, float zNear, float zFar);

	DLLEXPORT static Matrix4x4 CreateOrtho(float width, float height, float zNear, float zFar);

#pragma endregion

private:

#pragma region Init Functions

	DLLEXPORT void Init(float m00, float m01, float m02, float m03,
		      float m10, float m11, float m12, float m13,
			  float m20, float m21, float m22, float m23,
			  float m30, float m31, float m32, float m33);

	DLLEXPORT void InitFrustum(float left, float right, float bottom, float top, float zNear, float zFar);

	DLLEXPORT void InitOrtho(float width, float height, float zNear, float zFar);

#pragma endregion

public:

#pragma region Destructor

	DLLEXPORT virtual ~Matrix4x4();

#pragma endregion

#pragma region Overloaded Operators

	DLLEXPORT Matrix4x4 operator* (const Matrix4x4 & m) const;
    
    DLLEXPORT Vector4 operator* (const Vector4 & v) const;
    
    DLLEXPORT Matrix4x4 operator/ (float denominator) const;

#pragma endregion
    
#pragma region Matrix Methods
    
    // Transposes the matrix. Returns itself for chaining
    DLLEXPORT const Matrix4x4 & Transpose();
    
    // Inverts the matrix. Returns itself for chaining
    DLLEXPORT const Matrix4x4 & Invert();
    
#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT float GetValue(int rowIndex, int columnIndex) const;

	DLLEXPORT Vector3 GetTranslation() const;
    
    DLLEXPORT const float * GetArray() const;
    
    DLLEXPORT Vector3 GetForward() const;
    
    DLLEXPORT Vector3 GetUp() const;
    
    DLLEXPORT Vector3 GetRight() const;
    
    // Returns a matrix that is the transpose of this matrix
    DLLEXPORT Matrix4x4 GetTranspose() const;
    
    // Returns a matrix that is the inverse of this matrix
    DLLEXPORT Matrix4x4 GetInverse() const;
    
    // Returns the determinant of the matrix
    DLLEXPORT float GetDeterminant() const;
    
    // Returns the classical adjoint of the matrix
    DLLEXPORT Matrix4x4 GetAdjoint() const;

#pragma endregion

#pragma region Class Functions

	DLLEXPORT static Vector3 Transform(const Matrix4x4 & transform, const Vector3 & vector);

#pragma endregion

};

#pragma region Non member operator overloads

DLLEXPORT std::ostream & operator<< (std::ostream & o, const Matrix4x4 & m);

#pragma endregion
    
// Matrix inversion forward declarations
DLLEXPORT void MatrixInversion(float **A, int order, float **Y);
    
DLLEXPORT double CalcDeterminant( float **mat, int order);
    
DLLEXPORT int GetMinor(float **src, float **dest, int row, int col, int order);


}
}
