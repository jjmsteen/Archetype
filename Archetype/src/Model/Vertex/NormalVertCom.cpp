 
#include "stdafx.h"

#include "NormalVertCom.h"

using namespace AT;
using namespace Model;

NormalVertCom::NormalVertCom(const Maths::Vector3 & normal)
	: normal(normal)
{
}


NormalVertCom::~NormalVertCom()
{
}

const Maths::Vector3 & NormalVertCom::GetNormal()
{
	return normal;
}

void NormalVertCom::SetNormal(const Maths::Vector3 & normal)
{
	this->normal = normal;
}

unsigned short NormalVertCom::GetArrayLength() const
{
	return 3;
}

float * NormalVertCom::GetVertexAsArray()
{
	// Ensure the normal is normalised
	normal.Normalise();

	// Allocate an array of floats 
	float * vert = new float[this->GetArrayLength()];

	// Fill it with the data from the vector class
	vert[0] = normal.x;
	vert[1] = normal.y;
	vert[2] = normal.z;

	// Return a pointer to the array
	return vert;
}

std::vector<std::pair<std::string, unsigned short > > NormalVertCom::GetVertexDescription() const
{
    std::vector<std::pair<std::string, unsigned short > > v;
    
    v.push_back(std::pair<std::string, unsigned short >("normal", NormalVertCom::GetArrayLength()));
    
    return v;
}