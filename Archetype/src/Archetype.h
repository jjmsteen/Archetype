//
//  Archetype.h
//  Archetype
//
//  Created by Jay Steen on 28/09/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


// Maths includes
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Matrix2x2.h"
#include "SharedFunctions.h"


// Model includes
#include "GeometryFactory.h"
#include "Mesh.h"
#include "MeshAlias.h"
#include "Model3D.h"
#include "ModelLoader.h"
#include "ShaderEffect.h"

// Material includes
#include "Material.h"
#include "Texture.h"
#include "Colour.h"

// Vertex includes
#include "Vertex.h"
#include "VertexBuffer.h"
#include "SimpleVertex.h"

// Bounding includes
#include "BoundingFrustum.h"
#include "BoundingVolume.h"
#include "BoundingAABB.h"
#include "BoundingSphere.h"
#include "Octree.h"
#include "IBounded.h"

// Control includes
#include "Camera.h"

// Lighting includes
#include "Light.h"
#include "ShadowLight.h"
#include "PointLight.h"