#pragma once

// ** Vertex component for position ** //

#include "libPrefix.h"

#include "Vertex.h"
#include "Vector3.h"

namespace AT
{
namespace Model
{

class PositionVertCom
	: virtual public Vertex
{
protected:

	Maths::Vector3 position;

public:

#pragma region Constructors

	DLLEXPORT PositionVertCom(const Maths::Vector3 & position = Maths::Vector3::Zero());

#pragma endregion

#pragma region Denstructor

	DLLEXPORT virtual ~PositionVertCom(void);

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT const Maths::Vector3 & GetPosition();

	DLLEXPORT void SetPosition(const Maths::Vector3 & pos);
    
    // Returns a vector of pairs of strings with the name of the vertex components and the number of elements
    DLLEXPORT virtual std::vector<std::pair<std::string, unsigned short > > GetVertexDescription() const;

#pragma endregion

#pragma region Overridden Methods

	DLLEXPORT virtual unsigned short GetArrayLength() const;

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray();

#pragma endregion

};

}
}