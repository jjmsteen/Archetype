
#include "stdafx.h" 

#include "Face.h"

using namespace AT;
using namespace Model;

Face::Face(NormalVertCom & nv1, NormalVertCom & nv2, NormalVertCom & nv3,
		const Maths::Vector3 & pos1, const Maths::Vector3 & pos2, const Maths::Vector3 & pos3)
		: v1(nv1), v2(nv2), v3(nv3), faceNormal(CalculateFaceNormal(pos1, pos2, pos3))
{
}


Face::~Face()
{
}

Face & Face::operator= (const Face & f)
{
    this->v1 = f.v1;
    this->v2 = f.v2;
    this->v3 = f.v3;
    
    this->faceNormal = f.faceNormal;
    
    return *this;
}

void Face::AssignNormals()
{
	this->AssignNormal(v1);
	this->AssignNormal(v2);
	this->AssignNormal(v3);
}

void Face::AssignNormal(NormalVertCom & v)
{
	// Normalisation is not undertaken during this step as it skews the normal calculation

	// Get the normal from the vertex
	Maths::Vector3 vertexNormal = v.GetNormal();

	// Sum the current face and vertex normal
	vertexNormal += faceNormal;

	// If the length of the vertex normal is greater than 0 to float precision
	if (vertexNormal.LengthSquared() > 0.000001)
	{
		// Assign it back to the vertex
		v.SetNormal(vertexNormal);
	}

}

Maths::Vector3 Face::CalculateFaceNormal(const Maths::Vector3 & pos1, 
		const Maths::Vector3 & pos2, const Maths::Vector3 & pos3)
{
	// Get the distance from pos1 to pos2 and normalise
	Maths::Vector3 pos1to2 = pos2 - pos1;
	pos1to2.Normalise();

	// Get the distance from pos 1 to pos 3 and normalise
	Maths::Vector3 pos1to3 = pos3 - pos1;
	pos1to3.Normalise();

	// Get the cross product of 1-2 and 1-3 to give the perpendicular
	// vector, which is the face normal (in right handed coords)
	Maths::Vector3 normal = Maths::Vector3::Cross(pos1to2, pos1to3);

	// Normalise the normal
	normal.Normalise();

	// Return the normal
	return normal;
}