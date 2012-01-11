 
#include "stdafx.h"

#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "SharedFunctions.h"
#include <cmath>
#include <exception>

using namespace AT;
using namespace Maths;


#pragma region Constructors

// Create a default identity matrix
Matrix4x4::Matrix4x4() 
{
	Init(1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f);
}

// Create a matrix from axis scale values
Matrix4x4::Matrix4x4(float scaleX, float scaleY, float scaleZ)
{
	Init(scaleX, 0.0f,   0.0f,   0.0f,
		 0.0f,   scaleY, 0.0f,   0.0f,
		 0.0f,   0.0f,   scaleZ, 0.0f,
		 0.0f,   0.0f,   0.0f,   1.0f);
}

// Create a uniform scale matrix
Matrix4x4::Matrix4x4(float scale)
{
	Init(scale,  0.0f,   0.0f,   0.0f,
		 0.0f,   scale,  0.0f,   0.0f,
		 0.0f,   0.0f,   scale,  0.0f,
		 0.0f,   0.0f,   0.0f,   1.0f);
}

// Create a matrix from a translation
Matrix4x4::Matrix4x4(const Vector3 & translation)
{
	Init(1.0f, 0.0f, 0.0f, translation.x,
		 0.0f, 1.0f, 0.0f, translation.y,
		 0.0f, 0.0f, 1.0f, translation.z,
		 0.0f, 0.0f, 0.0f, 1.0f);

	/*Init(1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f, 0.0f,
		 translation.x, translation.y, translation.z, 1.0f);*/
}

// Create a matrix from a rotation (in radians) around an arbitrary axis
Matrix4x4::Matrix4x4(const Vector3 & axis, double angle)
{
	// Get sin and cosine of rotation angle
	float s, c;

	s = sin(angle);
	c = cos(angle);

	// Left handed rotation matrix
	/*matrix[0][0] = axis.x * axis.x * (1 - c) + c;
	matrix[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
	matrix[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
	matrix[0][3] = 0.0f;

	matrix[1][0] = axis.x * axis.y * (1 - c) + axis.z * s;
	matrix[1][1] = axis.y * axis.y * (1 - c) + c;
	matrix[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
	matrix[1][2] = 0.0f;

	matrix[2][0] = axis.x * axis.z * (1 - c) - axis.y * s;
	matrix[2][1] = axis.y * axis.z * (1 - c) + axis.x * s;
	matrix[2][2] = axis.z * axis.z * (1 - c) + c;
	matrix[2][3] = 0.0f;

	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;*/


	// Right handed rotation matrix
	/*matrix[0][0] = axis.x * axis.x * (1 - c) + c;
	matrix[0][1] = axis.x * axis.y * (1 - c) + axis.z * s;
	matrix[0][2] = axis.x * axis.z * (1 - c) - axis.y * s;
	matrix[0][3] = 0.0f;

	matrix[1][0] = axis.x * axis.y * (1 - c) - axis.z * s;
	matrix[1][1] = axis.y * axis.y * (1 - c) + c;
	matrix[1][2] = axis.y * axis.z * (1 - c) + axis.x * s;
	matrix[1][3] = 0.0f;

	matrix[2][0] = axis.x * axis.y * (1 - c) + axis.y * s;
	matrix[2][1] = axis.y * axis.z * (1 - c) - axis.x * s;
	matrix[2][2] = axis.z * axis.z * (1 - c) + c;
	matrix[2][3] = 0.0f;

	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;*/
    
    matrix[0] = axis.x * axis.x * (1 - c) + c;
	matrix[4] = axis.x * axis.y * (1 - c) + axis.z * s;
	matrix[8] = axis.x * axis.z * (1 - c) - axis.y * s;
	matrix[12] = 0.0f;
    
	matrix[1] = axis.x * axis.y * (1 - c) - axis.z * s;
	matrix[5] = axis.y * axis.y * (1 - c) + c;
	matrix[9] = axis.y * axis.z * (1 - c) + axis.x * s;
	matrix[13] = 0.0f;
    
	matrix[2] = axis.x * axis.y * (1 - c) + axis.y * s;
	matrix[6] = axis.y * axis.z * (1 - c) - axis.x * s;
	matrix[10] = axis.z * axis.z * (1 - c) + c;
	matrix[14] = 0.0f;
    
	matrix[3] = 0.0f;
	matrix[7] = 0.0f;
	matrix[11] = 0.0f;
	matrix[15] = 1.0f;
}

// Create a lookat matrix with an eye position, a focus position (lookat point) and up vector
Matrix4x4::Matrix4x4(const Vector3 & eyePosition, const Vector3 & focusPosition, const Vector3 & up)
{
	// Create a normalised forward vector
	Vector3 forward(focusPosition - eyePosition); 
	//Vector3 forward(eyePosition - focusPosition);
	forward.Normalise();
	
	// Compute the vector pointing right
	Vector3	side(Vector3::Cross(forward, up));
    //Vector3	side(Vector3::Cross(up, forward));
    side.Normalise();
		
	// Get the normal of the plane of the forward and side vectors (aka the real up)
	//Vector3	modifiedUp(Vector3::Cross(forward, side));
    Vector3 modifiedUp(Vector3::Cross(side, forward));

	// Initialise the view rotation matrix using the computed axes
//	Init(side.x, modifiedUp.x, -forward.x, -Vector3::Dot(side, eyePosition),
//         side.y, modifiedUp.y, -forward.y, -Vector3::Dot(modifiedUp, eyePosition),   
//         side.z, modifiedUp.z, -forward.z, -Vector3::Dot(forward, eyePosition),
//         0,      0,            0,         1);

	// Multiply this with the translation matrix implied by the eye position
	//*this = Matrix4x4(-eyePosition) * viewRotation;

	Init(side.x, side.y, side.z, -Vector3::Dot(side, eyePosition),
		 modifiedUp.x, modifiedUp.y, modifiedUp.z, -Vector3::Dot(modifiedUp, eyePosition),   
		 -forward.x, -forward.y, -forward.z, Vector3::Dot(forward, eyePosition),
		 0, 0, 0, 1);
}

// Create a frustum matrix
Matrix4x4::Matrix4x4(float left, float right, float bottom, float top, float zNear, float zFar)
{
	InitFrustum(left, right, bottom, top, zNear, zFar);
}

Matrix4x4::Matrix4x4(float fovY, float aspectRatio, float zNear, float zFar)
{
	//float yMax = zNear * tanf( fovY * PI / 360.0f );
    
    float yMax = zNear * tanf(fovY * 0.5f);
	float xMax = yMax * aspectRatio;

	// Initialise with a left/right and top/bottom values calculated above
	InitFrustum(-xMax, xMax, -yMax, yMax, zNear, zFar);
}

// Create an orthographic projection matrix
Matrix4x4::Matrix4x4(float width, float height, float zNear, float zFar, void * orthoMarker)
{
	InitOrtho(width, height, zNear, zFar);
}

// Create a matrix from an array of floats
Matrix4x4::Matrix4x4(float matrix[16])
{
    // Loop n' copy
    for (int i = 0; i < 16; ++i) this->matrix[i] = matrix[i];
}

// Create a matrix by specifying each component individually
Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33)
{
	Init(m00, m01, m02, m03,
		 m10, m11, m12, m13,
		 m20, m21, m22, m23,
		 m30, m31, m32, m33);
}

#pragma endregion

#pragma region Factory Methods

Matrix4x4 Matrix4x4::CreateScale(float scaleX, float scaleY, float scaleZ)
{
	return Matrix4x4(scaleX, scaleY, scaleZ);
}

Matrix4x4 Matrix4x4::CreateScale(float scale)
{
	return Matrix4x4(scale);
}

Matrix4x4 Matrix4x4::CreateRotation(const Vector3 & axis, double angleRadians)
{
	return Matrix4x4(axis, angleRadians);
}

Matrix4x4 Matrix4x4::CreateRotation(float yawRadians, float pitchRadians, float rollRadians)
{
    Matrix4x4 yawMat = Matrix4x4(Vector3::Up(), yawRadians);
    
    Vector3 rightTrans = Matrix4x4::Transform(yawMat, Vector3::Right());
    Matrix4x4 pitchMat = Matrix4x4(rightTrans, pitchRadians);
    
    Vector3 forwardTrans = Matrix4x4::Transform(pitchMat, Vector3::Forward());
    Matrix4x4 rollMat = Matrix4x4(forwardTrans, rollRadians);
    
    return rollMat * pitchMat * yawMat;
    
    return   Matrix4x4(Vector3::Forward(), rollRadians)
        * Matrix4x4(Vector3::Right(), pitchRadians)
        * Matrix4x4(Vector3::Up(), yawRadians);
    
    /*float rotation[16];
    
    rotation[0] = cosf(rollRadians) * cosf(yawRadians) - cosf(pitchRadians) * sinf(rollRadians) * sinf(yawRadians);
    rotation[1] = cosf(rollRadians) * sinf(yawRadians) + cosf(pitchRadians) * cosf(yawRadians) * sinf(rollRadians);
    rotation[2] = sinf(rollRadians) * sinf(yawRadians);
    rotation[3] = 0;
    
    rotation[4] = -sinf(rollRadians) * cosf(yawRadians) - cosf(pitchRadians) * sinf(yawRadians) * cosf(rollRadians);
    rotation[5] = -sinf(rollRadians) * sinf(yawRadians) + cosf(pitchRadians) * cosf(yawRadians) * cosf(rollRadians);
    rotation[6] = cosf(rollRadians) * sinf(pitchRadians);
    rotation[7] = 0;
    
    rotation[8] = sinf(pitchRadians) * sinf(yawRadians);
    rotation[9] = -sinf(pitchRadians) * cosf(yawRadians);
    rotation[10] = cosf(pitchRadians);
    rotation[11] = 0;
    
    rotation[12] = 0;
    rotation[13] = 0;
    rotation[14] = 0;
    rotation[15] = 1;
    
    return Matrix4x4(rotation);*/
    
}

Matrix4x4 Matrix4x4::CreateTranslation(const Vector3 & translation)
{
	return Matrix4x4(translation);
}

Matrix4x4 Matrix4x4::CreateLookAt(const Vector3 & eyePosition, const Vector3 & focusPosition, const Vector3 & up)
{
	return Matrix4x4(eyePosition, focusPosition, up);
}

Matrix4x4 Matrix4x4::CreatePerspective(float fovY, float aspectRatio, float zNear, float zFar)
{
	return Matrix4x4(fovY, aspectRatio, zNear, zFar);
}

Matrix4x4 Matrix4x4::CreateFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
	return Matrix4x4(left, right, bottom, top, zNear, zFar);
}

Matrix4x4 Matrix4x4::CreateOrtho(float width, float height, float zNear, float zFar)
{
	return Matrix4x4(width, height, zNear, zFar, 0);
}

#pragma endregion

#pragma region Init Functions

void Matrix4x4::Init(float m00, float m01, float m02, float m03,
					 float m10, float m11, float m12, float m13,
					 float m20, float m21, float m22, float m23,
					 float m30, float m31, float m32, float m33)
{
//	matrix[0][0] = m00; matrix[0][1] = m01; matrix[0][2] = m02; matrix[0][3] = m03;
//	matrix[1][0] = m10; matrix[1][1] = m11; matrix[1][2] = m12; matrix[1][3] = m13;
//	matrix[2][0] = m20; matrix[2][1] = m21; matrix[2][2] = m22; matrix[2][3] = m23;
//	matrix[3][0] = m30; matrix[3][1] = m31; matrix[3][2] = m32; matrix[3][3] = m33;
    
    matrix[0] = m00;
    matrix[1] = m10;
    matrix[2] = m20;
    matrix[3] = m30;
    
    matrix[4] = m01;
    matrix[5] = m11;
    matrix[6] = m21;
    matrix[7] = m31;
    
    matrix[8] =  m02;
    matrix[9] =  m12;
    matrix[10] = m22;
    matrix[11] = m32;
    
    matrix[12] = m03;
    matrix[13] = m13;
    matrix[14] = m23;
    matrix[15] = m33;
}

void Matrix4x4::InitFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
	// From http://www.songho.ca/opengl/gl_projectionmatrix.html

	float doubleNear = 2.0 * zNear;

	// Width
	float width = right - left;

	// Height
	float height = top - bottom;

	// Depth
	float depth = zFar - zNear;

	/*Init(doubleNear / width, 0, 0, 0,
		0, doubleNear / height, 0, 0,
		(right + left) / (width), (top + bottom) / (height), -(zFar + zNear) / depth, -1,
		0, 0, (zFar * -doubleNear) / depth, 0);*/


	// Right handed projection matrix
//	Init(doubleNear / width,	0,	 (right + left) / width,	0,
//		 0,		doubleNear / height, (top + bottom) / height,	0,
//		 0,		0,		-(zFar + zNear) / depth,	(-2 * zFar * zNear) / depth,
//		 0,		0,		-1,		0);
    
    Init(doubleNear / width,	0,	 (right + left) / width,	0,
		 0,		doubleNear / height, (top + bottom) / height,	0,
		 0,		0,		-(zFar + zNear) / depth,	(-2 * zFar * zNear) / depth,
		 0,		0,		-1,		0);
}

void Matrix4x4::InitOrtho(float width, float height, float zNear, float zFar)
{
	// From http://www.codeguru.com/cpp/misc/misc/math/article.php/c10123__2/

//	Init(2 / width, 0, 0, 0,
//		0, 2 / height, 0, 0,
//		0, 0, 1 / (zFar - zNear), 0,
//		0, 0, -zNear / (zFar - zNear), 1);
    
    Init(2.0f / width, 0, 0, 0,
         0, 2.0f / height, 0, 0,
         0, 0, -2.0f / (zFar - zNear), - ((zFar + zNear) / (zFar - zNear)),
         0, 0, 0, 1.0);
    
//    Init(2.0f / width, 0, 0, 0,
//         0, 2.0f / height, 0, 0,
//         0, 0, -2.0f / (zFar - zNear), 0,
//         0, 0, - ((zFar + zNear) / (zFar - zNear)), 1.0);

}

#pragma endregion

#pragma region Destructor

Matrix4x4::~Matrix4x4()
{
}

#pragma endregion

#pragma region Overloaded Operators

Matrix4x4 Matrix4x4::operator* (const Matrix4x4 & m) const
{
	Matrix4x4 retMatrix;

	// Loop over the rows of the new matrix
	for (int row = 0; row < 4; ++row)
	{
		// Loop over the columns of the new matrix
		for (int col = 0; col < 4; ++col)
		{
            // ** Old 4x4 array code
			// Compute the inner product of the row and 
			// column of the matrices being multiplied
			/*retMatrix.matrix[row][col] = 
				matrix[row][0] * m.matrix[0][col] +
				matrix[row][1] * m.matrix[1][col] + 
				matrix[row][2] * m.matrix[2][col] +
				matrix[row][3] * m.matrix[3][col];*/
            
            // 1D Array code
            retMatrix.matrix[col * 4 + row] =
                matrix[0 + row] * m.matrix[col * 4 + 0] +
                matrix[4 + row] * m.matrix[col * 4 + 1] +
                matrix[8 + row] * m.matrix[col * 4 + 2] +
                matrix[12 + row] * m.matrix[col * 4 + 3];
		}
	}

	return retMatrix;
}

Vector4 Matrix4x4::operator* (const Vector4 & v) const
{
    return Vector4(matrix[0] * v.x + matrix[4] * v.y + matrix[8] * v.z + matrix[12] * v.w,
                   matrix[1] * v.x + matrix[5] * v.y + matrix[9] * v.z + matrix[13] * v.w,
                   matrix[2] * v.x + matrix[6] * v.y + matrix[10] * v.z + matrix[14] * v.w,
                   matrix[3] * v.x + matrix[7] * v.y + matrix[11] * v.z + matrix[15] * v.w);
}

Matrix4x4 Matrix4x4::operator/ (float denominator) const
{
    // Prevent divide by zero softly
    if (denominator == 0.0f)
        denominator = 1.0f;
    
    // Initialise the return matrix
    Matrix4x4 m(*this);
    
    // Divide all the elements by the denominator
    for (int i = 0; i < 16; ++i) 
        m.matrix[i] /= denominator;
    
    return m;
}

#pragma endregion

#pragma region Matrix Methods

// Transposes the matrix. Returns itself for chaining
const Matrix4x4 & Matrix4x4::Transpose()
{
    *this = this->GetTranspose();
    return *this;
}

// Inverts the matrix. Returns itself for chaining
const Matrix4x4 & Matrix4x4::Invert()
{
    *this = this->GetInverse();
    return *this;
}

#pragma endregion

#pragma region Getters and Setters

float Matrix4x4::GetValue(int rowIndex, int columnIndex) const
{
	// Check to ensure the indices are in bounds
	// If not, throw an exception
	if (rowIndex > 3 || rowIndex < 0 
		|| columnIndex > 3 || columnIndex < 0)
#ifdef WIN32
		throw std::exception("Index to matrix out of bounds.");
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
        throw "Index to matrix out of bounds.";
#else
        throw -1;
#endif
    
    // Old 4x4 array code
	//return matrix[rowIndex][columnIndex];
    return matrix[columnIndex * 4 + rowIndex];
}

Vector3 Matrix4x4::GetTranslation() const
{
    // Old 4x4 array code
	//return Vector3(matrix[0][3], matrix[1][3], matrix[2][3]);
    
    return Vector3(matrix[12], matrix[13], matrix[14]);
}

const float * Matrix4x4::GetArray() const
{ 
    return matrix; 
}

Vector3 Matrix4x4::GetForward() const
{
    return Vector3(matrix[8], matrix[9], matrix[10]);
}

Vector3 Matrix4x4::GetUp() const
{
    return Vector3(matrix[4], matrix[5], matrix[6]);
}

Vector3 Matrix4x4::GetRight() const
{
    return Vector3(matrix[0], matrix[1], matrix[2]);
}

Matrix4x4 Matrix4x4::GetTranspose() const
{
    return Matrix4x4(matrix[0], matrix[1], matrix[2], matrix[3],
                     matrix[4], matrix[5], matrix[6], matrix[7],
                     matrix[8], matrix[9], matrix[10], matrix[11],
                     matrix[12], matrix[13], matrix[14], matrix[15]);
}

Matrix4x4 Matrix4x4::GetInverse() const
{
    //return this->GetAdjoint() / this->GetDeterminant();
    
    //Matrix4x4 m = this->GetAdjoint() / this->GetDeterminant();
    
    
    // Set up a 4x4 array to hold this matrix's values
    int order = 4;
    float ** mat = new float*[order];
    float ** invMat = new float*[order];
    
    for (int i = 0; i < order; ++i) 
    {
        mat[i] = new float[order];
        invMat[i] = new float[order];
        for (int j = 0; j < order; ++j) 
        {
            mat[i][j] = this->GetValue(i, j);
        }
    }
    
    
    
    MatrixInversion(mat, order, invMat);
    
    Matrix4x4 m(invMat[0][0], invMat[0][1], invMat[0][2], invMat[0][3],
                     invMat[1][0], invMat[1][1], invMat[1][2], invMat[1][3],
                     invMat[2][0], invMat[2][1], invMat[2][2], invMat[2][3],
                     invMat[3][0], invMat[3][1], invMat[3][2], invMat[3][3]);

    
    delete[] invMat;
    delete[] mat;
    
    return m;
}

float Matrix4x4::GetDeterminant() const
{
    // From p128 of 3D Math Primer for Graphics and Game Development
    
    return matrix[0] * (matrix[5] * (matrix[10] * matrix[15] - matrix[14] * matrix[11])) 
        - matrix[6] * (matrix[9] * matrix[15] + matrix[13] * matrix[11])
        + matrix[7] * (matrix[9] * matrix[14] - matrix[13] * matrix[10])
        - matrix[1] * (matrix[4] * (matrix[10] * matrix[15] - matrix[14] * matrix[11]))
        - matrix[6] * (matrix[8] * matrix[15] + matrix[12] * matrix[11])
        + matrix[7] * (matrix[8] * matrix[14] - matrix[12] * matrix[10])
        + matrix[2] * (matrix[4] * (matrix[9] * matrix[15] - matrix[13] * matrix[11]))
        - matrix[5] * (matrix[8] * matrix[15] + matrix[12] * matrix[11])
        + matrix[7] * (matrix[8] * matrix[13] - matrix[12] * matrix[9])
        - matrix[3] * (matrix[4] * (matrix[9] * matrix[14] - matrix[13] * matrix[10]))
        - matrix[5] * (matrix[8] * matrix[14] + matrix[12] * matrix[10])
        + matrix[6] * (matrix[8] * matrix[13] - matrix[12] * matrix[9]);
}

Matrix4x4 Matrix4x4::GetAdjoint() const
{
    float cofactors[16];
    
    // Loop over rows and columns
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col) 
        {
            // Cofactors alternate between positive and negative signs and are the determinant of the minor of that row and column
            cofactors[col * 4 + row] = powf(-1.0f, row + col + 2.0f) * (Matrix3x3::CreateMinorOf(*this, row, col)).GetDeterminant();
        }
    }
    
    Matrix4x4 adj(cofactors);
    
    // The classical adjoint is the transpose of the matrix of cofactors
    return adj.Transpose();
}

#pragma endregion

#pragma region Class Functions

Vector3 Matrix4x4::Transform(const Matrix4x4 & transform, const Vector3 & vector)
{
	Vector3 retVector = vector;

	// For whether the vector is considered as a point or a vector
	// (if a point, translation is applied, otherwise not)
	//float w = 1.0f;
	//float retW = 1.0f;


	//retVector.x = transform.GetValue(0,0) * vector.x + 
	//	transform.GetValue(0,1) * vector.y + 
	//	transform.GetValue(0,2) * vector.z;// + 
	//	//transform.GetValue(0,3) * w;

	//retVector.y = transform.GetValue(1,0) * vector.x + 
	//	transform.GetValue(1,1) * vector.y + 
	//	transform.GetValue(1,2) * vector.z;// + 
	//	//transform.GetValue(1,3) * w;

	//retVector.z = transform.GetValue(2,0) * vector.x + 
	//	transform.GetValue(2,1) * vector.y + 
	//	transform.GetValue(2,2) * vector.z; //+ 
	//	//transform.GetValue(2,3) * w;

	//retW = transform.GetValue(3,0) * vector.x + 
	//	transform.GetValue(3,1) * vector.y + 
	//	transform.GetValue(3,2) * vector.z; //+ 
	//	//transform.GetValue(3,3) * w;


	// Perform the rotation component
	retVector.x = transform.GetValue(0,0) * vector.x + 
		transform.GetValue(1,0) * vector.y + 
		transform.GetValue(2,0) * vector.z;

	retVector.y = transform.GetValue(0,1) * vector.x + 
		transform.GetValue(1,1) * vector.y + 
		transform.GetValue(2,1) * vector.z;

	retVector.z = transform.GetValue(0,2) * vector.x + 
		transform.GetValue(1,2) * vector.y + 
		transform.GetValue(2,2) * vector.z;

//	retW = transform.GetValue(0,3) * vector.x + 
//		transform.GetValue(1,3) * vector.y + 
//		transform.GetValue(2,3) * vector.z;

	// Perform the translation component
	retVector.x += transform.GetValue(0,3);
	retVector.y += transform.GetValue(1,3);
	retVector.z += transform.GetValue(2,3);

	// Return the temporary return vector
	return retVector;
}

#pragma endregion

#pragma region Non-member operator overloads

namespace AT
{
namespace Maths
{

std::ostream & operator<< (std::ostream & o, const Matrix4x4 & m)
{
	return o << "[\t" << ZeroSmallFloat(m.GetValue(0,0)) << ",\t" << ZeroSmallFloat(m.GetValue(0,1)) 
		<< ",\t" << ZeroSmallFloat(m.GetValue(0,2)) << ",\t" << ZeroSmallFloat(m.GetValue(0,3)) << "\t]\n"

		<< "[\t" << ZeroSmallFloat(m.GetValue(1,0)) << ",\t" << ZeroSmallFloat(m.GetValue(1,1)) 
		<< ",\t" << ZeroSmallFloat(m.GetValue(1,2)) << ",\t" << ZeroSmallFloat(m.GetValue(1,3)) << "\t]\n"

		<< "[\t" << ZeroSmallFloat(m.GetValue(2,0)) << ",\t" << ZeroSmallFloat(m.GetValue(2,1)) 
		<< ",\t" << ZeroSmallFloat(m.GetValue(2,2)) << ",\t" << ZeroSmallFloat(m.GetValue(2,3)) << "\t]\n"

		<< "[\t" << ZeroSmallFloat(m.GetValue(3,0)) << ",\t" << ZeroSmallFloat(m.GetValue(3,1)) 
		<< ",\t" << ZeroSmallFloat(m.GetValue(3,2)) << ",\t" << ZeroSmallFloat(m.GetValue(3,3)) << "\t]\n";
}
	
}
}

#pragma endregion

#pragma region Copied Inverse Code

namespace AT 
{
namespace Maths
{


// Code used with kind permission from http://chi3x10.wordpress.com/2008/05/28/calculate-matrix-inversion-in-c/

// matrix inversioon
// the result is put in Y
void MatrixInversion(float **A, int order, float **Y)
{
    // get the determinant of a
    double det = 1.0/CalcDeterminant(A,order);
    
    // memory allocation
    float *temp = new float[(order-1)*(order-1)];
    float **minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = temp+(i*(order-1));
    
    for(int j=0;j<order;j++)
    {
        for(int i=0;i<order;i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(A,minor,j,i,order);
            Y[i][j] = det*CalcDeterminant(minor,order-1);
            if( (i+j)%2 == 1)
                Y[i][j] = -Y[i][j];
        }
    }
    
    // release memory
    //delete [] minor[0];
    delete [] temp;
    delete [] minor;
}

// calculate the cofactor of element (row,col)
int GetMinor(float **src, float **dest, int row, int col, int order)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;
    
    for(int i = 0; i < order; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < order; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }
    
    return 1;
}

// Calculate the determinant recursively.
double CalcDeterminant( float **mat, int order)
{
    // order must be >= 0
	// stop the recursion when matrix is a single element
    if( order == 1 )
        return mat[0][0];
    
    // the determinant value
    float det = 0;
    
    // allocate the cofactor matrix
    float **minor;
    minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = new float[order-1];
    
    for(int i = 0; i < order; i++ )
    {
        // get minor of element (0,i)
        GetMinor( mat, minor, 0, i , order);
        // the recusion is here!
        
        det += (i%2==1?-1.0:1.0) * mat[0][i] * CalcDeterminant(minor,order-1);
        //det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
    }
    
    // release memory
    for(int i=0;i<order-1;i++)
        delete [] minor[i];
    delete [] minor;
    
    return det;
}
    
}
}


#pragma endregion