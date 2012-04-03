 
#include "stdafx.h"

#include "VertexBuffer.h"

using namespace AT;
using namespace Model;

VertexBuffer::VertexBuffer(const std::vector<Vertex*> & vertexList, const std::vector<unsigned short> & indexList)
	: vertexCount(vertexList.size()), singleVertexLength(vertexList[0]->GetArrayLength()),
	indexCount(indexList.size()), vbImpl(0), vertexDescription(vertexList[0]->GetVertexDescription())
{	

	// Create the vertex buffer based on the length of the vector
	// and the vertex type's length as an array
	vertices = new float[vertexCount * singleVertexLength];

	// Loop over the vertex List and put the elements in the vertex buffer
	for (int i = 0; i < vertexList.size(); i++)
	{
		// Get the current vertex
		Vertex * currentElement = vertexList[i];

		// If its length is not the same as the first element's, throw an exception
		if (currentElement->GetArrayLength() != singleVertexLength)
		{
			// Delete the dynamically allocated vertices memory
			delete[] vertices;

			throw "Elements of the vertex array are not the same type.";
		}

		// Create the array for the current vertex
		float * currentVertArray = currentElement->GetVertexAsArray();

		// Loop over the array returned from the vertex and copy it in
		for (int j = 0; j < currentElement->GetArrayLength(); j++)
		{
			// Copy the current vert's value into the vertex buffer
			vertices[i * singleVertexLength + j] = currentVertArray[j];
		}

		// Delete the current vertex's array after its values have been copied
		delete[] currentVertArray;

	}

	// Create an index buffer based on the length of the index list
	indices = new unsigned short[indexList.size()];

	// Loop over the index list
	for (int i = 0; i < indexList.size(); i++)
	{
		// Assign its value to the array
		indices[i] = indexList[i];
	}

}

VertexBuffer::VertexBuffer(const VertexBuffer & vb)
	: vertexCount(vb.vertexCount), singleVertexLength(vb.singleVertexLength),
	indexCount(vb.indexCount), vertexDescription(vb.vertexDescription)
{
	// Create a new float buffer of the size of the passed one
	this->vertices = new float[vertexCount * singleVertexLength];

	// Loop over the array and copy
	for (int i = 0; i < vertexCount * singleVertexLength; i++)
	{
		this->vertices[i] = vb.vertices[i];
	}

	// Create a new index buffer of the length of the passed one
	this->indices = new unsigned short[indexCount];

	// Loop over the array and copy
	for (int i = 0; i < indexCount; i++)
	{
		this->indices[i] = vb.indices[i];
	}
    
    // If the vertex buffer has an implementation, clone that beggar
    if (vb.vbImpl)
        this->vbImpl = (vb.vbImpl->CloneThisObject());

}


VertexBuffer::~VertexBuffer()
{
	// If there is a vertex buffer, delete it
	if (vertices)
		delete[] vertices;

	// If there is an index buffer, delete it
	if (indices)
		delete[] indices;
	
	// If there is a bridge class, delete it
	if (vbImpl != 0)
		delete vbImpl; 
}

float const * VertexBuffer::GetVertexBufferData() const
{
	return vertices;
}

unsigned short const * VertexBuffer::GetIndexBufferData() const
{
	return indices;
}

void VertexBuffer::SetBridge(VBBridge * bridge)
{
	// Delete the current bridge if it's there
	if (vbImpl != 0)
		delete vbImpl; 

	vbImpl = bridge;
}

void VertexBuffer::GenerateVertexBuffer()
{
	if (vbImpl)
		vbImpl->GenerateVertexBuffer(vertices, vertexCount * singleVertexLength, indices, indexCount);
}

void VertexBuffer::MakeActive()
{
	if (vbImpl)
		vbImpl->MakeActive();
}