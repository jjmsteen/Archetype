#pragma once

#include "libPrefix.h"

#include "PositionVertCom.h"
#include "TexCoordVertCom.h"
#include "NormalVertCom.h"

namespace AT
{
namespace Model
{

class SimpleVertex
	: virtual public PositionVertCom, 
	  virtual public TexCoordVertCom,
	  virtual public NormalVertCom
{
public:

#pragma region Constructor/Destructor

	DLLEXPORT SimpleVertex(const Maths::Vector3 & position, 
		const Maths::Vector2 & texCoords, 
		const Maths::Vector3 & normal);

	DLLEXPORT virtual ~SimpleVertex(void);

#pragma endregion

#pragma region Overridden Methods

	DLLEXPORT virtual unsigned short GetArrayLength() const;

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray();
    
    DLLEXPORT virtual std::vector<std::pair<std::string, unsigned short > > GetVertexDescription() const;

#pragma endregion

};

}
}
