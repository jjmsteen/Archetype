 
#include "stdafx.h"
#include <cmath>

#include "Camera.h"

using namespace AT;
using namespace Control;
using namespace Bounding;

static const float KF_SINGULARITY_OFFSET = 0.02f;

Camera::Camera(void)
	: eyePosition(Maths::Vector3()), focusPosition(Maths::Vector3(0,0,-1)), worldUp(Maths::Vector3::Up()), zNear(0.1f), zFar(1000.0f)
{
	this->CalculateView();

	projection = Maths::Matrix4x4::CreatePerspective(2.0f, 4.0f/3.0f, zNear, zFar);
}


Camera::Camera(const Maths::Vector3 & eyePosition, const Maths::Vector3 & focusPosition, 
	const Maths::Vector3 & worldUp, float fovY, float aspectRatio, float zNear, float zFar)
	: eyePosition(eyePosition), focusPosition(focusPosition), worldUp(worldUp), zNear(zNear), zFar(zFar)
{
	this->CalculateView();

	this->SetProjectionPerspective(fovY, aspectRatio, zNear, zFar);
}



Camera::~Camera(void)
{
}

#pragma region Getters and Setters

// Gets the eye's position
const Maths::Vector3 & Camera::GetEyePosition() const { return eyePosition; }
// Sets the eye's position to the position passed in
void Camera::SetEyePosition(const Maths::Vector3 & eyePos) 
{
	eyePosition = eyePos;
	CalculateView();
}
// Adds the vector passed in to the camera position
void Camera::TranslateEyePosition(const Maths::Vector3 & eyeTranslation)
{
	eyePosition += eyeTranslation;
	CalculateView();
}

// Gets the focus position
const Maths::Vector3 & Camera::GetFocusPosition() const { return focusPosition; }
// Sets the focus position to the position passed in
void Camera::SetFocusPosition(const Maths::Vector3 & focusPos) 
{
	focusPosition = focusPos;
	CalculateView();
}
// Adds the vector passed in to the focus position
void Camera::TranslateFocusPosition(const Maths::Vector3 & focusTranslation)
{
	focusPosition += focusTranslation;
	CalculateView();
}

// Gets the world up vector
const Maths::Vector3 & Camera::GetWorldUp() const { return worldUp; }
// Sets the world up vector
void Camera::SetWorldUp(const Maths::Vector3 & worldUp)
{
	this->worldUp = worldUp;
	CalculateView();
}

// Sets the whole look at portion
DLLEXPORT void Camera::SetView(const Maths::Vector3 & eyePosition, const Maths::Vector3 & focusPosition, const Maths::Vector3 & worldUp)
{
    this->eyePosition = eyePosition; 
    this->focusPosition = focusPosition;
    this->worldUp = worldUp;
    
    this->CalculateView();
}

// Get the view matrix
const Maths::Matrix4x4 & Camera::GetView() const { return view; }

// Get the projection matrix
const Maths::Matrix4x4 & Camera::GetProjection() const { return projection; }

// Set the projection matrix to a symmetrical perspective projection
void Camera::SetProjectionPerspective(float fovY, float aspectRatio, float zNear, float zFar)
{
	projection = Maths::Matrix4x4::CreatePerspective(fovY, aspectRatio, zNear, zFar);
    
    this->zNear = zNear;
    this->zFar = zFar;
    
    this->fovyRadians = fovY;
    this->aspect = aspectRatio;
    
    float yMax = zNear * tanf(fovY * 0.5f);
	float xMax = yMax * aspectRatio;
    this->farPlaneHeight = yMax * 2.0f;
    this->farPlaneWidth = xMax * 2.0f;
}

// Set the projection matrix to an arbitrary frustum
void Camera::SetProjectionFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
	projection = Maths::Matrix4x4::CreateFrustum(left, right, bottom, top, zNear, zFar);
    
    this->zNear = zNear;
    this->zFar = zFar;
    
    this->farPlaneWidth = right + -left;
    this->farPlaneHeight = top + -bottom;
}
// Set the projection matrix to be orthographic
void Camera::SetProjectionOrthographic(float width, float height, float zNear, float zFar)
{    
	projection = Maths::Matrix4x4::CreateOrtho(width, height, zNear, zFar);
    
    this->zNear = zNear;
    this->zFar = zFar;
    
    this->farPlaneWidth = width;
    this->farPlaneHeight = height;
}

// Get the camera-related up vector
const Maths::Vector3 & Camera::GetCameraUp() const { return cameraUp; } 
// Get the forward vector
const Maths::Vector3 & Camera::GetForward() const { return forward; }
// Get the side vector
const Maths::Vector3 & Camera::GetSide() const { return side; }

Bounding::BoundingFrustum Camera::GetBoundingFrustum() const
{
    return BoundingFrustum(this->projection * this->view);
}

#pragma endregion

void Camera::CalculateView()
{
	// Calculate the forward unit vector
	forward = focusPosition - eyePosition;
	forward.Normalise();

	// Normalise the world up vector
	worldUp.Normalise();

	// Get the right (side) vector
	side = Maths::Vector3::Cross(forward, worldUp);
	side.Normalise();

	// Get the camera up
	cameraUp = Maths::Vector3::Cross(side, forward);
	cameraUp.Normalise();

	view = Maths::Matrix4x4::CreateLookAt(eyePosition, focusPosition, cameraUp);

}

void Camera::Dolly(const Maths::Vector3 & translation)
{
	this->TranslateEyePosition(translation);
	this->TranslateFocusPosition(translation);
}

void Camera::MoveTo(const Maths::Vector3 & position)
{
    // Set the eye and the focus position
    focusPosition = position + forward;
    eyePosition = position;
    
    // Recalculate view
    this->CalculateView();
}

void Camera::Pan(float yawRadians, float pitchRadians)
{
    // Remove the view offset
    focusPosition -= eyePosition;
    
    // Create a rotation matrix
    Maths::Matrix4x4 rotation = Maths::Matrix4x4::CreateRotation(Maths::Vector3::Up(), yawRadians);
    
    // Rotate the focus position around the 'eye' origin
    focusPosition = Maths::Matrix4x4::Transform(rotation, focusPosition);
    
    // Also rotate the side vector
    side = Maths::Matrix4x4::Transform(rotation, side);
    
    // Create a new rotation matrix around the altered side vector for pitch
    rotation = Maths::Matrix4x4::CreateRotation(side, pitchRadians);
    
    // Apply this rotation
    focusPosition = Maths::Matrix4x4::Transform(rotation, focusPosition);
    
    // Reintroduce the view offset
    focusPosition += eyePosition;
    
    // Recalculate the view matrix
    this->CalculateView();
    
    
}

void Camera::Orbit(float yawRadians, float pitchRadians)
{
    // Remove the view offset
    eyePosition -= focusPosition;
    
	// Create a rotation matrix
	Maths::Matrix4x4 rotation = Maths::Matrix4x4::CreateRotation(cameraUp, yawRadians);
    
    // Rotate the eye position around the 'focus' origin
    eyePosition = Maths::Matrix4x4::Transform(rotation, eyePosition);
    
    // Also rotate the side vector
    side = Maths::Matrix4x4::Transform(rotation, side);
    
	// Create a new rotation matrix around the altered side vector for pitch
	rotation = Maths::Matrix4x4::CreateRotation(side, pitchRadians);
    
	// Apply this rotation to the eye position and the forward vector
	Maths::Vector3 lNewEyePos = Maths::Matrix4x4::Transform(rotation, eyePosition);
	Maths::Vector3 lNewForward = -lNewEyePos;
	lNewForward.Normalise();

	// Get the dot between the world up and the new forward to see how close we are to the singularity
	float lUpForwardDot = Maths::Vector3::Dot(worldUp, lNewForward);

	// If we're not close to the singularities
	if ((1.0f - fabs(lUpForwardDot)) > KF_SINGULARITY_OFFSET)
	{
		eyePosition = lNewEyePos;
	}
    
    // Reintroduce the view offset
    eyePosition += focusPosition;
    
    // Recalculate the view matrix
    this->CalculateView();

}