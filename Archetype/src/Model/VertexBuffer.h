#pragma once

#include <vector>
#include <utility>
#include <string>

#include "libPrefix.h"

#include "Vertex.h"
#include "ShaderEffect.h"
#include "VBBridge.h"

namespace AT
{
namespace Model
{
    
    // A helpful typedef to save typing all that
    typedef std::vector<std::pair<std::string, unsigned short> > VertexDescription;

class VertexBuffer
{
protected:

	// Buffer of floats for storing all vertex data
	float * vertices;

	// The number of vertices in the buffer
	const unsigned int vertexCount;

	// The length of a single vertex
	const unsigned int singleVertexLength;

	// Buffer of indices for indexing the stored vertices
	unsigned short * indices;
	// The number of indices in the buffer
	const unsigned int indexCount;

	// The bridge object for implementing vertex buffer storage
	VBBridge * vbImpl;
    
    // An ordered list of pairs of names and value counts of the attribute
    std::vector<std::pair<std::string, unsigned short> > vertexDescription;

public:

#pragma region Constructors

	// Assumes that the vector of vertices contains only one vertex type
	DLLEXPORT VertexBuffer(const std::vector<Vertex*> & vertexList, const std::vector<unsigned short> & indexList);

	// Copy constructor
	DLLEXPORT VertexBuffer(const VertexBuffer & vb);

#pragma endregion

#pragma region Destructors

	DLLEXPORT virtual ~VertexBuffer();

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT float const * GetVertexBufferData() const;

	DLLEXPORT unsigned short const * GetIndexBufferData() const;
    
    DLLEXPORT unsigned int GetVertCount() const { return vertexCount; }
    
    DLLEXPORT unsigned int GetVertexArrayLength() const { return vertexCount * singleVertexLength; }
    
    DLLEXPORT unsigned int GetIndexArrayLength() const { return indexCount; }
    
    DLLEXPORT const std::vector<std::pair<std::string, unsigned short> > &GetVertexDescription() const { return vertexDescription; }
    
    DLLEXPORT unsigned int GetSingleVertexLength() const { return singleVertexLength; }

#pragma endregion

#pragma region Loading and Activation

	// Set the bridge class that deals with the platform dependent implementation
	DLLEXPORT void SetBridge(VBBridge * bridge);

	// Creates the platform side vertex buffer object
	DLLEXPORT void GenerateVertexBuffer();

	// Make this vertex buffer the active vertex buffer
	DLLEXPORT void MakeActive();

#pragma endregion

};

}
}