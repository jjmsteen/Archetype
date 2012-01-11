#pragma once

#include "libPrefix.h"

#include "Vertex.h"
#include "Vector3.h"

namespace AT
{
namespace Model
{

class NormalVertCom :
	virtual public Vertex
{
protected:

	Maths::Vector3 normal;

public:

#pragma region Constructor and Destructor

	DLLEXPORT NormalVertCom(const Maths::Vector3 & normal = Maths::Vector3::Zero());

	DLLEXPORT ~NormalVertCom();

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetNormal();

	DLLEXPORT void SetNormal(const Maths::Vector3 & normal);

#pragma endregion

#pragma region Overridden Methods

	DLLEXPORT virtual unsigned short GetArrayLength() const;

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray();
    
    // Returns a vector of pairs of strings with the name of the vertex components and the number of elements
    DLLEXPORT virtual std::vector<std::pair<std::string, unsigned short > > GetVertexDescription() const;

#pragma endregion

};

}
}