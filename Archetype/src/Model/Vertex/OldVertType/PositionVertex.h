#pragma once

#include "libPrefix.h"

#include "Vertex.h"
#include "Vector3.h"

#include <vector>

namespace AT
{
namespace Model
{

class PositionVertex
	: public Vertex
{
protected:
		
	Maths::Vector3 position;

public:

#pragma region Constructors

	DLLEXPORT PositionVertex();

	DLLEXPORT PositionVertex(const Maths::Vector3 & position);

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetPosition();
	DLLEXPORT void SetPosition(const Maths::Vector3 & pos);

#pragma endregion

#pragma region Public Members

	// Returns the length the vertex would be as an array
	DLLEXPORT virtual unsigned short GetArrayLength();

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray();

#pragma endregion

#pragma region Destructor

	DLLEXPORT virtual ~PositionVertex();

#pragma endregion

};

}
}