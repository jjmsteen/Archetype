 
#include "StdAfx.h" 

#include "SimpleVertex.h"

using namespace AT;
using namespace Model;

SimpleVertex::SimpleVertex(const Maths::Vector3 & position, 
		const Maths::Vector2 & texCoords, 
		const Maths::Vector3 & normal)
		: PositionVertCom(position),
		  TexCoordVertCom(texCoords),
		  NormalVertCom(normal)
{
}


SimpleVertex::~SimpleVertex()
{
}

unsigned short SimpleVertex::GetArrayLength() const
{
	// Get sum of all of the vertex components' lengths
	return PositionVertCom::GetArrayLength()
		+ TexCoordVertCom::GetArrayLength()
		+ NormalVertCom::GetArrayLength();
}

float * SimpleVertex::GetVertexAsArray()
{
	// Get the float arrays of the respective components
	float * positionComponent = PositionVertCom::GetVertexAsArray();
	float * texCoordComponent = TexCoordVertCom::GetVertexAsArray();
	float * normalComponent = NormalVertCom::GetVertexAsArray();

	// Create one array to hold them all
	float * simpleVert = new float[this->GetArrayLength()];

	// Copy position
	for (int i = 0; i < PositionVertCom::GetArrayLength(); i++)
	{
		simpleVert[i] = positionComponent[i];
	}

	// Copy texcoord
	for (int i = 0; i < TexCoordVertCom::GetArrayLength(); i++)
	{
		simpleVert[i + PositionVertCom::GetArrayLength()] = texCoordComponent[i];
	}

	// Copy normal
	for (int i = 0; i < NormalVertCom::GetArrayLength(); i++)
	{
		simpleVert[i + PositionVertCom::GetArrayLength() 
			+ TexCoordVertCom::GetArrayLength()] = normalComponent[i];
	}

	// Delete the separate float arrays
	delete[] positionComponent;
	delete[] texCoordComponent;
	delete[] normalComponent;

	return simpleVert;
}

std::vector<std::pair<std::string, unsigned short > > SimpleVertex::GetVertexDescription() const
{
    // Create a return vector object
    std::vector<std::pair<std::string, unsigned short > > v;
    
    // Get the position component's description
    std::vector<std::pair<std::string, unsigned short > > posComDesc = PositionVertCom::GetVertexDescription();
    
    // Put it in the return vector
    v.assign(posComDesc.begin(), posComDesc.end());
    
    // Get the normal component's description
    std::vector<std::pair<std::string, unsigned short > > texComDesc = TexCoordVertCom::GetVertexDescription();
    
    // Put it in the return container
    v.insert(v.end(), texComDesc.begin(), texComDesc.end());
    
    // Get the normal component's description
    std::vector<std::pair<std::string, unsigned short > > normComDesc = NormalVertCom::GetVertexDescription();
    
    // Put it in the return container
    v.insert(v.end(), normComDesc.begin(), normComDesc.end());
    
    // Return the container
    return v;
}