#pragma once

#include "libPrefix.h"

#include "Vertex.h"
#include "Vector2.h"

namespace AT
{
namespace Model
{

class TexCoordVertCom :
	virtual public Vertex
{
protected:

	Maths::Vector2 texCoords;

public:

#pragma region Constructor/Destructor

	DLLEXPORT TexCoordVertCom(const Maths::Vector2 & texCoords = Maths::Vector2::Zero());

	DLLEXPORT virtual ~TexCoordVertCom(void);

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector2 & GetTexCoords();

	DLLEXPORT void SetTexCoords(const Maths::Vector2 & texCoords);

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
