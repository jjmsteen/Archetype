#pragma once

#include "libPrefix.h"

// A vertex buffer is a concept implemented on almost all 3D graphics systems,
// however the methods for implementing them are platform dependent.
// Therefore this bridge class is provided and must be subclassed for each system that 
// uses the system.

namespace AT
{
namespace Model
{

class VBBridge
{

public:

	DLLEXPORT VBBridge(void);

	DLLEXPORT virtual ~VBBridge(void);

	DLLEXPORT virtual void GenerateVertexBuffer(const float * vertices, unsigned int vertArrayLength, 
		const unsigned short * indices, unsigned int indArrayLength) = 0;

	DLLEXPORT virtual void MakeActive() = 0;

#pragma region Cloning methods

	DLLEXPORT virtual VBBridge * CreateNewObject() const = 0;

	DLLEXPORT virtual VBBridge * CloneThisObject() const = 0;

#pragma endregion
};

}
}