 
#include "stdafx.h" 

#include "TexCoordVertCom.h"

using namespace AT;
using namespace Model;

TexCoordVertCom::TexCoordVertCom(const Maths::Vector2 & texCoords)
	: texCoords(texCoords)
{
}


TexCoordVertCom::~TexCoordVertCom(void)
{
}

const Maths::Vector2 & TexCoordVertCom::GetTexCoords()
{
	return texCoords;
}

void TexCoordVertCom::SetTexCoords(const Maths::Vector2 & texCoords)
{
    this->texCoords = texCoords;
}

unsigned short TexCoordVertCom::GetArrayLength() const
{
	return 2;
}

float * TexCoordVertCom::GetVertexAsArray()
{
	// Allocate an array of floats 
	float * vert = new float[this->GetArrayLength()];

	// Fill it with the data from the vector class
	vert[0] = texCoords.x;
	vert[1] = texCoords.y;

	// Return a pointer to the array
	return vert;
}


std::vector<std::pair<std::string, unsigned short > > TexCoordVertCom::GetVertexDescription() const
{
    std::vector<std::pair<std::string, unsigned short > > v;
    
    v.push_back(std::pair<std::string, unsigned short >("texCoord", TexCoordVertCom::GetArrayLength()));
    
    return v;
}