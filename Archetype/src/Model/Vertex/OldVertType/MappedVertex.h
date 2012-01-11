#pragma once

#include "PositionVertex.h"

#include "Maths\Vector2.h"
#include "Maths\Vector3.h"


namespace AT
{
namespace Model
{

class MappedVertex :
	public PositionVertex
{

protected:

	Maths::Vector2 UVs;

public:

#pragma region Constructors

	DLLEXPORT MappedVertex();

	DLLEXPORT MappedVertex(const Maths::Vector3 & position, const Maths::Vector2 & UVs);

#pragma endregion

#pragma region Destructors

	DLLEXPORT virtual ~MappedVertex();

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector2 & GetUVs();
	DLLEXPORT void SetUVs(const Maths::Vector2 & uv);

#pragma endregion

#pragma region Public Methods

	// Returns the length the vertex would be as an array
	DLLEXPORT virtual unsigned short GetArrayLength();

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray();

#pragma endregion

};

}
}