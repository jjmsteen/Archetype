//
//  ShadowLight.cpp
//  Archetype
//
//  Created by Jay Steen on 21/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <cmath>

#include "ShadowLight.h"
#include "GeometryFactory.h"
#include "MeshAlias.h"
#include "Vector4.h"
#include "Matrix3x3.h"

using namespace AT; using namespace Lighting;

std::vector<Maths::Vector3> ShadowLight::GetFrustumCornersWS() const
{
    // This method draws heavily upon http://zach.in.tu-clausthal.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
    
    using namespace Maths;
    
    std::vector<Vector3> corners;
    
    float far = viewerCamera.GetFar();
    
    // Get the centre point of the far plane
    Vector3 farCentre = viewerCamera.GetForward() * far;
    
    // Get the top left of the frustum
    corners.push_back(farCentre 
                   + (viewerCamera.GetCameraUp() * (far * viewerCamera.GetFarPlaneHeight() * 0.5f))
                   - (viewerCamera.GetSide() * (far * viewerCamera.GetFarPlaneWidth() * 0.5f)));
    
    // Get the top right of the frustum
    corners.push_back(farCentre 
                   + (viewerCamera.GetCameraUp() * (far * viewerCamera.GetFarPlaneHeight() * 0.5f))
                   + (viewerCamera.GetSide() * (far * viewerCamera.GetFarPlaneWidth() * 0.5f)));
    
    // Get the bottom right of the frustum
    corners.push_back(farCentre 
                   - (viewerCamera.GetCameraUp() * (far * viewerCamera.GetFarPlaneHeight() * 0.5f))
                   + (viewerCamera.GetSide() * (far * viewerCamera.GetFarPlaneWidth() * 0.5f)));
    
    // Get the bottom left of the frustum
    corners.push_back(farCentre 
                   - (viewerCamera.GetCameraUp() * (far * viewerCamera.GetFarPlaneHeight() * 0.5f))
                   - (viewerCamera.GetSide() * (far * viewerCamera.GetFarPlaneWidth() * 0.5f)));
    
    return corners; 
}

ShadowLight::ShadowLight(const Control::Camera & viewerCamera, const Model::MeshAlias & fullScreenQuad, const Maths::Vector3 & lightDirection, float sceneRadius, const Model::Colour & diffuseColour)
: Light(fullScreenQuad, diffuseColour), viewerCamera(viewerCamera), direction(lightDirection), sceneRadius(sceneRadius)
{
    Camera::SetView(viewerCamera.GetEyePosition() + (-direction * sceneRadius), viewerCamera.GetEyePosition(), Maths::Vector3::Up());
    
    Camera::SetProjectionOrthographic(10.0f, 10.0f, 1.0f, sceneRadius);
}

LightType ShadowLight::GetLightType() const
{
    return LIGHT_SHADOW;
}

void ShadowLight::Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader)
{
    
}

void ShadowLight::Update()
{
    using namespace Maths;
    
    // Get the corner points of the viewer's frustum
    std::vector<Vector3> corners = GetFrustumCornersWS();
    
    // Treat the viewer position as a corner for ease's sake
    corners.push_back(viewerCamera.GetEyePosition());
    
    // The world space centroid
    Vector3 wsCentroid(0,0,0);
    
    Vector3 wsMax(corners[0]); Vector3 wsMin(corners[0]); Vector3 vsMax; Vector3 vsMin;
    
    // Orient the corners and viewer position to light view space, keeping track of vsMax and vsMin points
    for (int i = 0; i < corners.size(); ++i) 
    {
        wsCentroid += corners[i];
        
        // Update the worldspace max and min first
        wsMax.x = corners[i].x > wsMax.x ? corners[i].x : wsMax.x;
        wsMax.y = corners[i].y > wsMax.y ? corners[i].y : wsMax.y;
        wsMax.z = corners[i].z > wsMax.z ? corners[i].z : wsMax.z;
        
        wsMin.x = corners[i].x < wsMin.x ? corners[i].x : wsMin.x;
        wsMin.y = corners[i].y < wsMin.y ? corners[i].y : wsMin.y;
        wsMin.z = corners[i].z < wsMin.z ? corners[i].z : wsMin.z;
        
//        // Reorient to light view space
//        corners[i] = Vector3(Camera::GetView() * Vector4(corners[i], 1.0f));
//        
//        // Update the view space max and min
//        vsMax.x = corners[i].x > vsMax.x ? corners[i].x : vsMax.x;
//        vsMax.y = corners[i].y > vsMax.y ? corners[i].y : vsMax.y;
//        vsMax.z = corners[i].z > vsMax.z ? corners[i].z : vsMax.z;
//        
//        vsMin.x = corners[i].x < vsMin.x ? corners[i].x : vsMin.x;
//        vsMin.y = corners[i].y < vsMin.y ? corners[i].y : vsMin.y;
//        vsMin.z = corners[i].z < vsMin.z ? corners[i].z : vsMin.z;
    }   
    
    wsCentroid *= 0.2f;
    Vector3 wsCentroid2 = (wsMax + wsMin) * 0.5;
    
    // Set the view matrix
    Camera::SetView(wsCentroid + (-direction * sceneRadius * 2.0f), wsCentroid, Vector3::Up());
    
    // Set the ortho projection
//    Camera::SetProjectionOrthographic(vsMax.x - vsMin.x, vsMax.y - vsMin.y, 1.0f, fabs(vsMin.z));
    Camera::SetProjectionOrthographic(1000.0f, 1000.0f, 1.0f, 10000.0f);

}



