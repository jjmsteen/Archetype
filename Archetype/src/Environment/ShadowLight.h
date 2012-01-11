//
//  ShadowLight.h
//  Archetype
//
//  Created by Jay Steen on 21/11/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <set>
#include <vector>

#include "Light.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "ShaderEffect.h"

namespace AT 
{
    
namespace Lighting
{
    
class ShadowLight
    : public Light,
    public Control::Camera
{
    // A constant reference to the viewer's camera, 
    // to keep track of movement so the shadow map is as precise as possible
    const Control::Camera & viewerCamera;
    
    // Get the viewer's frustum corners in world space
    std::vector<Maths::Vector3> GetFrustumCornersWS() const;
    
    // The direction of the light
    Maths::Vector3 direction;
    
    // The smallest distance the light should be from the camera to encompass the whole scene
    const float sceneRadius;
    
public:
    
    DLLEXPORT ShadowLight(const Control::Camera & viewerCamera, const Model::MeshAlias & fullScreenQuad, const Maths::Vector3 & lightDirection, float sceneRadius, const Model::Colour & diffuseColour);
    
    DLLEXPORT const Maths::Vector3 & GetDirection() const { return direction; }
    
    DLLEXPORT virtual LightType GetLightType() const;
    
//    DLLEXPORT void DrawDepthMap(const std::set<Renderable*> & litObjects, const Model::ShaderEffect & shader);
    
    DLLEXPORT virtual void Draw(const Maths::Matrix4x4 & View, const Maths::Matrix4x4 & Projection, Model::ShaderEffect & shader);
    
    // Update the projection and view matrices to maximise the precision in the depth map
    DLLEXPORT void Update();
        
};

}
}