#pragma once

#include "libPrefix.h"

#include "Matrix4x4.h"
#include "Vector3.h"
#include "BoundingFrustum.h"

namespace AT
{
namespace Control
{

class Camera
{
protected:

	// The position of the camera
	Maths::Vector3 eyePosition;

	// The location the camera is focussed upon
	Maths::Vector3 focusPosition;

	// The world up vector
	Maths::Vector3 worldUp;

	// The viewing transform matrix for this camera
	Maths::Matrix4x4 view;
	
	// The projection matrix employed by this camera
	Maths::Matrix4x4 projection;

	Maths::Vector3 cameraUp;

	Maths::Vector3 forward;

	Maths::Vector3 side;
    
    // The field of view and aspect ratios
    float fovyRadians;
    float aspect;
    
    // The near and far distances
    float zNear;
    float zFar;
    
    // The width and height of the far plane
    float farPlaneWidth;
    float farPlaneHeight;

public:

#pragma region Constructors / Destructor

	DLLEXPORT Camera();
    
//    DLLEXPORT Camera(const Maths::Vector3 & eyePosition, const Maths::Vector3 & focusPosition, 
//                     const Maths::Vector3 & worldUp, const Maths::Matrix4x4 & projection);

	DLLEXPORT Camera(const Maths::Vector3 & eyePosition, const Maths::Vector3 & focusPosition, 
		const Maths::Vector3 & worldUp, float fovY, float aspectRatio, float zNear, float zFar);
    
    

	DLLEXPORT virtual ~Camera(void);

#pragma endregion

#pragma region Getters and Setters

	// Gets the eye's position
	DLLEXPORT const Maths::Vector3 & GetEyePosition() const;
	// Sets the eye's position to the position passed in
	DLLEXPORT void SetEyePosition(const Maths::Vector3 & eyePos);
	// Adds the vector passed in to the camera position
	DLLEXPORT void TranslateEyePosition(const Maths::Vector3 & eyeTranslation);

	// Gets the focus position
	DLLEXPORT const Maths::Vector3 & GetFocusPosition() const;
	// Sets the focus position to the position passed in
	DLLEXPORT void SetFocusPosition(const Maths::Vector3 & focusPos);
	// Adds the vector passed in to the focus position
	DLLEXPORT void TranslateFocusPosition(const Maths::Vector3 & focusTranslation);

	// Gets the world up vector
	DLLEXPORT const Maths::Vector3 & GetWorldUp() const;
	// Sets the world up vector
	DLLEXPORT void SetWorldUp(const Maths::Vector3 & worldUp);
    
    // Sets the whole look at portion
    DLLEXPORT void SetView(const Maths::Vector3 & eyePosition, const Maths::Vector3 & focusPosition, 
                           const Maths::Vector3 & worldUp);

	// Get the view matrix
	DLLEXPORT const Maths::Matrix4x4 & GetView() const;

	// Get the projection matrix
	DLLEXPORT const Maths::Matrix4x4 & GetProjection() const;

	// Set the projection matrix to a symmetrical perspective projection
	DLLEXPORT void SetProjectionPerspective(float fovY, float aspectRatio, float zNear, float zFar);
	// Set the projection matrix to an arbitrary frustum
	DLLEXPORT void SetProjectionFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	// Set the projection matrix to be orthographic
	DLLEXPORT void SetProjectionOrthographic(float width, float height, float zNear, float zFar);

	// Get the camera-related up vector
	DLLEXPORT const Maths::Vector3 & GetCameraUp() const;
	// Get the forward vector
	DLLEXPORT const Maths::Vector3 & GetForward() const;
	// Get the side vector
	DLLEXPORT const Maths::Vector3 & GetSide() const;
    
    // Get the fovY in radians
    DLLEXPORT float GetFOVY() const { return fovyRadians; }
    // Get the aspect ratio
    DLLEXPORT float GetAspect() const { return aspect; }
    
    // Get the near distance
    DLLEXPORT float GetNear() const { return zNear; }
    // Get the far distance
    DLLEXPORT float GetFar() const { return zFar; }
    // Get the far plane height
    DLLEXPORT float GetFarPlaneHeight() const { return farPlaneHeight; }
    // Get the far plane width
    DLLEXPORT float GetFarPlaneWidth() const { return farPlaneWidth; }
    
    // Returns the bounding frustum of this camera
    DLLEXPORT Bounding::BoundingFrustum GetBoundingFrustum() const;


#pragma endregion

#pragma region Private Methods

	// Recalculates the view matrix based on changes to 
	// other variables
	DLLEXPORT void CalculateView();

#pragma endregion

#pragma region Movement Methods

	DLLEXPORT void Dolly(const Maths::Vector3 & translation);
    
    // Moves the camera and the focus position simultaneously 
    DLLEXPORT void MoveTo(const Maths::Vector3 & position);
    
    //DLLEXPORT void PanCamera(const Maths::Matrix4x4 & rotationMatrix);
    
    // Rotate the focus position relative to the eye position
    DLLEXPORT void Pan(float yawRadians, float pitchRadians);
    
    // Rotate the camera position relative to the focus position
    DLLEXPORT void Orbit(float yawRadians, float pitchRadians);

#pragma endregion

};

} 
}