#pragma once

/* * 
 * * Class Face : Used for calculating normals for the face 
 * * and assigning them to the vertices.
 * *
 * */


#include "libPrefix.h"

#include "Vector3.h"

#include "Vertex.h"
#include "NormalVertCom.h"

namespace AT
{
namespace Model
{

class Face
{
	// References to each of the 3 vertices, so they can be changed directly in this class

	// First vertex
	NormalVertCom & v1;

	// Second vertex
	NormalVertCom & v2;

	// Third vertex
	NormalVertCom & v3;

	// Face normal
	Maths::Vector3 faceNormal;

public:

#pragma region Constructor/Destructor

	DLLEXPORT Face(NormalVertCom & nv1, NormalVertCom & nv2, NormalVertCom & nv3,
		const Maths::Vector3 & pos1, const Maths::Vector3 & pos2, const Maths::Vector3 & pos3);

	DLLEXPORT ~Face();

#pragma endregion
    
#pragma region OAO / Copy Constructor
    
    // Overloaded assignment operator
    DLLEXPORT Face & operator= (const Face & f);
    
#pragma endregion

#pragma region Public Methods

	DLLEXPORT void AssignNormals();

#pragma endregion

private: 

#pragma region Private Methods

	DLLEXPORT Maths::Vector3 CalculateFaceNormal(const Maths::Vector3 & pos1, 
		const Maths::Vector3 & pos2, const Maths::Vector3 & pos3);

	DLLEXPORT void AssignNormal(NormalVertCom & v);

#pragma endregion

};

}
}
