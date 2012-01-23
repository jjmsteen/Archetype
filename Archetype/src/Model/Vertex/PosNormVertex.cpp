 
#include "stdafx.h" 

#include "PosNormVertex.h"

using namespace AT;
using namespace Model;

PosNormVertex::PosNormVertex(const Maths::Vector3 & position, 
		const Maths::Vector3 & normal)
		: PositionVertCom(position), NormalVertCom(normal)
{
}


PosNormVertex::~PosNormVertex(void)
{
}

unsigned short PosNormVertex::GetArrayLength() const
{
	return PositionVertCom::GetArrayLength() + NormalVertCom::GetArrayLength();
}

float * PosNormVertex::GetVertexAsArray()
{
	// Get the vertex components as arrays
	float * positionComponent = PositionVertCom::GetVertexAsArray();
	float * normalComponent = PositionVertCom::GetVertexAsArray();

	// Create an array to hold both
	float * posNormVert = new float[this->GetArrayLength()];

	// Copy the position component in
	for (int i = 0; i < PositionVertCom::GetArrayLength(); i++)
	{
		posNormVert[i] = positionComponent[i];
	}

	// Copy the normal component in
	for (int i = 0; i < NormalVertCom::GetArrayLength(); i++)
	{
		posNormVert[i + PositionVertCom::GetArrayLength()] = normalComponent[i];
	}

	return posNormVert;
}

std::vector<std::pair<std::string, unsigned short > > PosNormVertex::GetVertexDescription() const
{
    // Create a return vector object
    std::vector<std::pair<std::string, unsigned short > > v;
    
    // Get the position component's description
    std::vector<std::pair<std::string, unsigned short > > posComDesc = PositionVertCom::GetVertexDescription();
    
    // Debug variables
//    std::string s = posComDesc[0].first;
//    unsigned short us = posComDesc[0].second;
    
    // Put it in the return vector
    v.assign(posComDesc.begin(), posComDesc.end());
    
//    s = v[0].first;
//    us = v[0].second;
    
    // Get the normal component's description
    std::vector<std::pair<std::string, unsigned short > > normComDesc = NormalVertCom::GetVertexDescription();
    
//    s = normComDesc[0].first;
//    us = normComDesc[0].second;
    
    // Put it in the return container
    v.insert(v.end(), normComDesc.begin(), normComDesc.end());
    
//    s = v[0].first;
//    us = v[0].second;
    
    // Return the container
    return v;
}