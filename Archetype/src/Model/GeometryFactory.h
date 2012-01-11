#pragma once

#include "libPrefix.h"

#include "Mesh.h"
#include "RenderBridge.h"
#include "VBBridge.h"


namespace AT
{
namespace Model
{

class GeometryFactory
{
public:

	static RenderBridge * renderBridge;

	static VBBridge * vbBridge;

private:

	GeometryFactory(void);
	virtual ~GeometryFactory(void);
    
    DLLEXPORT static void SetVBBridge(VertexBuffer & vb);
    
    DLLEXPORT static void SetRenderBridge(Mesh & m);

public:

	DLLEXPORT static void SetVBBridgePrototype(VBBridge * vb);
	DLLEXPORT static void SetRenderBridgePrototype(RenderBridge * r);

	DLLEXPORT static Mesh * Sphere(float radius, unsigned int slices, unsigned int stacks);

	DLLEXPORT static Mesh * Cone(float height, float radius, unsigned int slices);
    
    DLLEXPORT static Mesh * TexturedQuad(float width, float height, bool twoSided);
};

}
}