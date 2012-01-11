 
#include "StdAfx.h"


#include "PositionVertex.h"

using namespace AT;
using namespace Model;

PositionVertex::PositionVertex()
	: position(0, 0, 0)
{
}

PositionVertex::PositionVertex(const Maths::Vector3 & position)
	: position(position)
{
}

int PositionVertex::GetArrayLength()
{
	return 3;
}

const Maths::Vector3 & PositionVertex::GetPosition()
{
	return this->position;
}

void PositionVertex::SetPosition(const Maths::Vector3 & pos)
{
	this->position = pos;
}

float * PositionVertex::GetVertexAsArray()
{
	// Allocate an array of floats 
	float * vert = new float[this->GetArrayLength()];

	// Fill it with the data from the vector class
	vert[0] = position.x;
	vert[1] = position.y;
	vert[2] = position.z;

	// Return a pointer to the array
	return vert;
}

PositionVertex::~PositionVertex()
{
}
