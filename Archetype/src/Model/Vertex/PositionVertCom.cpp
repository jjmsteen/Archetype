
#include "StdAfx.h"

#include "PositionVertCom.h"

using namespace AT;
using namespace Model;

PositionVertCom::PositionVertCom(const Maths::Vector3 & position)
	: position(position)
{
}


PositionVertCom::~PositionVertCom(void)
{
}

const Maths::Vector3 & PositionVertCom::GetPosition()
{
	return this->position;
}

void PositionVertCom::SetPosition(const Maths::Vector3 & pos)
{
	this->position = pos;
}

std::vector<std::pair<std::string, unsigned short > > PositionVertCom::GetVertexDescription() const
{
    std::vector<std::pair<std::string, unsigned short > > v;
    
    v.push_back(std::pair<std::string, unsigned short >("position", PositionVertCom::GetArrayLength()));
    
    return v;
}

unsigned short PositionVertCom::GetArrayLength() const
{
	return 3;
}

float * PositionVertCom::GetVertexAsArray()
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