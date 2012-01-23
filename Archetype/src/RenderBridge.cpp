#include "stdafx.h"
#include "RenderBridge.h"

using namespace AT;

RenderBridge::RenderBridge()
: vertexBuffer(0), shaderEffect(0)
{
}


RenderBridge::~RenderBridge(void)
{
}

void RenderBridge::SetVertexBuffer(Model::VertexBuffer * vb)
{
    if (vb)
    {
        // Don't do any memory management as the arrays don't belong to this object
        vertexBuffer = vb;
    }
}

void RenderBridge::SetShaderEffect(Model::ShaderEffect * sh)
{
    if (sh)
    {
        shaderEffect = sh;
    }
    
}