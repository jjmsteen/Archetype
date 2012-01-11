#pragma once

#include "PositionVertCom.h"
#include "NormalVertCom.h"

namespace AT
{
namespace Model
{

class PosNormVertex :
	virtual public PositionVertCom,
	virtual public NormalVertCom
{
public:

#pragma region Constructor/Destructor

	DLLEXPORT PosNormVertex(const Maths::Vector3 & position, 
		const Maths::Vector3 & normal);

	DLLEXPORT virtual ~PosNormVertex(void);

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