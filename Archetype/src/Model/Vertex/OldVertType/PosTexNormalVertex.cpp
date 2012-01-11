
#include "StdAfx.h" 

#include "PosTexNormalVertex.h"

using namespace AT;
using namespace Model;

PosTexNormalVertex::PosTexNormalVertex()
	: MappedVertex(), normal(0, 1, 0)
{
}

PosTexNormalVertex::PosTexNormalVertex(const Maths::Vector3 & position, const Maths::Vector2 & UVs, const Maths::Vector3 & normal)
	: MappedVertex(position, UVs), normal(normal)
{
}


PosTexNormalVertex::~PosTexNormalVertex()
{
}

const Maths::Vector3 & PosTexNormalVertex::GetNormal()
{
	return this->normal;
}

void PosTexNormalVertex::SetNormal(const Maths::Vector3 & norm)
{
	this->normal = norm;
}

int PosTexNormalVertex::GetArrayLength()
{
	return 3 + MappedVertex::GetArrayLength();
}

float * PosTexNormalVertex::GetVertexAsArray()
{
	// Get the dynamically allocated array of the superclass vertex
	float * superVert = MappedVertex::GetVertexAsArray();

	// Allocate some new memory for the float array
	float * vert = new float[this->GetArrayLength()];

	// Get the length of the superclass array
	int superArrayLength = MappedVertex::GetArrayLength();

	// Copy values of superclass vertex into new array
	for (int i = 0; i < superArrayLength; i++)
	{
		vert[i] = superVert[i];
	}

	// Put the values in the array
	vert[superArrayLength] = normal.x;
	vert[superArrayLength + 1] = normal.y;
	vert[superArrayLength + 2] = normal.z;

	// Delete the old storage allocated by the superclass vertex
	delete[] superVert;

	// Return the concatenated array
	return vert;
}