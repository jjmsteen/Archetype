 
#include "StdAfx.h"

#include "MappedVertex.h"

using namespace AT;
using namespace Model;

MappedVertex::MappedVertex()
{
}

MappedVertex::MappedVertex(const Maths::Vector3 & position, const Maths::Vector2 & UVs)
	: PositionVertex(position), UVs(UVs)
{
}


MappedVertex::~MappedVertex()
{
}

const Maths::Vector2 & MappedVertex::GetUVs()
{
	return this->UVs;
}

void MappedVertex::SetUVs(const Maths::Vector2 & uv)
{
	this->UVs = uv;
}

int MappedVertex::GetArrayLength()
{
	return 2 + PositionVertex::GetArrayLength();
}

float * MappedVertex::GetVertexAsArray()
{
	// Get the dynamically allocated array of the superclass vertex
	float * superVert = PositionVertex::GetVertexAsArray();

	// Allocate some new memory for the float array
	float * vert = new float[this->GetArrayLength()];

	// Get the length of the superclass array
	int superArrayLength = PositionVertex::GetArrayLength();

	// Copy values of superclass vertex into new array
	for (int i = 0; i < superArrayLength; i++)
	{
		vert[i] = superVert[i];
	}

	// Put the values in the array
	vert[superArrayLength] = UVs.x;
	vert[superArrayLength + 1] = UVs.y; 

	// Delete the old storage allocated by the superclass vertex
	delete[] superVert;

	// Return the concatenated array
	return vert;
}