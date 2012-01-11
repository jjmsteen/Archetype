#pragma once
#include "MappedVertex.h"
#include "Maths\Vector3.h"
#include "Maths\Vector2.h"

namespace AT
{
namespace Model
{

class PosTexNormalVertex :
	public MappedVertex
{

protected:

	Maths::Vector3 normal;

public:

#pragma region Constructors

	DLLEXPORT PosTexNormalVertex();

	DLLEXPORT PosTexNormalVertex(const Maths::Vector3 & position, const Maths::Vector2 & UVs, const Maths::Vector3 & normal);

#pragma endregion

#pragma region Destructors

	DLLEXPORT virtual ~PosTexNormalVertex();

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetNormal();
	DLLEXPORT void SetNormal(const Maths::Vector3 & norm);

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