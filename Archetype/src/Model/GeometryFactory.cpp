 
#include "stdafx.h" 

#include "GeometryFactory.h"
#include "SharedFunctions.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "Face.h"
#include "PosNormVertex.h"
#include "SimpleVertex.h"

#include "BoundingSphere.h"
#include "BoundingAABB.h"

#include <vector>

using namespace AT;
using namespace Model;

// Static variables
AT::RenderBridge * GeometryFactory::renderBridge = 0;
VBBridge * GeometryFactory::vbBridge = 0;

GeometryFactory::GeometryFactory(void)
{
}


GeometryFactory::~GeometryFactory(void)
{
}

void GeometryFactory::SetVBBridge(VertexBuffer & vb)
{
	// If there is a vertex buffer bridge, copy it into the vb object
	if (GeometryFactory::vbBridge)
		vb.SetBridge(GeometryFactory::vbBridge->CreateNewObject());
}

void GeometryFactory::SetRenderBridge(Mesh & m)
{
	// If there is a render bridge, copy it on to the mesh object
	if (GeometryFactory::renderBridge)
		m.SetRenderer(GeometryFactory::renderBridge->CreateNewObject());
}

void GeometryFactory::SetVBBridgePrototype(VBBridge * vb)
{
	vbBridge = vb;
}

void GeometryFactory::SetRenderBridgePrototype(RenderBridge * r)
{
	renderBridge = r;
}

Mesh * GeometryFactory::Sphere(float radius, unsigned int slices, unsigned int stacks)
{
	// Stops rendering errors as having less than 2 of either
	// means the sphere will render incorrectly
	if (slices < 2)
		slices = 2;

	if (stacks < 2)
		stacks = 2;

	// The rotation that is to be applied around the y axis to move to the next slice
	double rotation = (Maths::PI * 2) / slices;
	Maths::Matrix4x4 sliceRotation(Maths::Vector3::Up(), rotation);

	// The rotation that is to be applied around the x axis to move to the next stack
	rotation = (Maths::PI) / stacks;
	Maths::Matrix4x4 stackRotation(Maths::Vector3::Right(), rotation);

	// A list holding vertex positions
	std::vector<Maths::Vector3> vertPositions;

	// The first position is always the radius directly above the origin
	Maths::Vector3 position(0, radius, 0);

	// A list holding index positions
	std::vector<unsigned short> indices;

	// Add the first position to the list
	vertPositions.push_back(position);

	// Add the first indices from the top of the sphere
	for (unsigned int i = 0; i < slices; i++)
	{
		indices.push_back(0);
		indices.push_back((i + 1) % slices + 1);
		indices.push_back((i + 2) % slices + 1);
	}

	// Do one less stack than the count because the last is always a single point,
	// similar to the top
	for (unsigned int stackNumber = 0; stackNumber < stacks - 1; stackNumber++)
	{
		// Apply the stack rotation (around the x axis)
		position = Maths::Matrix4x4::Transform(stackRotation, position);

		// Avoid accumulating error by creating a local copy of the new position
		// for this loop iteration
		Maths::Vector3 slicePosition(position);

		// Loop through the slices
		for (unsigned int sliceNumber = 0; sliceNumber < slices; sliceNumber++)
		{
			// Put the position into the list
			vertPositions.push_back(slicePosition);

			// Use a different routine for the final stack as it is irregular
			if (stackNumber < stacks - 2U)
			{
				// Add the indices, six for each middle vert
				// First triangle
				indices.push_back((stackNumber * slices + sliceNumber + 1));
				indices.push_back(((stackNumber + 1) * slices + sliceNumber + 1));
				indices.push_back((stackNumber * slices) + (sliceNumber + 1) % slices + 1);
				// Second triangle
				indices.push_back(((stackNumber + 1) * slices + sliceNumber + 1));
				indices.push_back(((stackNumber + 1) * slices) + (sliceNumber + 1) % slices + 1);
				indices.push_back((stackNumber * slices) + (sliceNumber + 1) % slices + 1);
			}
			else
			{
				// Only one tri, as there is a single point at the base of the sphere
				indices.push_back((stackNumber * slices + sliceNumber + 1));
				indices.push_back((stacks - 1) * slices + 1);
				indices.push_back((stackNumber * slices) + (sliceNumber + 1) % slices + 1);
			}

			// Apply the slice rotation (around y axis)
			slicePosition = Maths::Matrix4x4::Transform(sliceRotation, slicePosition);
		}
	}

	// Set the final position
	position = Maths::Vector3(0, -radius, 0);
	vertPositions.push_back(position);

	// Create a list for the vertices
	std::vector<Vertex*> verts;

	for (unsigned int i = 0; i < vertPositions.size(); i++)
	{
		// The normal for a vertex is simply the vector from the origin to its 
		// position, normalised, as this is a regular sphere
		Maths::Vector3 normal = vertPositions[i];
		normal.Normalise();

		verts.push_back(new PosNormVertex(vertPositions[i], normal));
	}

	// Create a vertex buffer from the verts and inds
	VertexBuffer vb(verts, indices);

	SetVBBridge(vb);
	vb.GenerateVertexBuffer();

	// Delete the gumpf in the vertex list
	for (unsigned int i = 0; i < verts.size(); i++) delete verts[i];
	
	// That's all we need
	Mesh * m = new Mesh("Sphere", Maths::Matrix4x4(), vb, new Bounding::BoundingSphere(Maths::Vector3(), radius));

	SetRenderBridge(*m);

	return m;


}

Mesh * GeometryFactory::Cone(float height, float radius, unsigned int slices)
{
	// A cone needs to have 3 or more sides to render properly
	if (slices < 3)
		slices = 3;

	// Declarations

	// The rotation that is to be applied around the y axis to move to the next slice
	double rotation = (Maths::PI * 2) / slices;
	Maths::Matrix4x4 sliceRotation(Maths::Vector3::Up(), rotation);

	// A list holding vertex positions
	std::vector<Maths::Vector3> vertPositions;

	// The first position is always at the origin
	Maths::Vector3 position(0, 0, 0);

	// A list holding index positions
	std::vector<unsigned short> indices;

	// Add the first position to the list
	vertPositions.push_back(position);

	// Lower the height to the base of the cone
	position.y -= height;
	// Move the lateral position out by the radius
	position.z += radius;

	for (unsigned int sliceNum = 0; sliceNum < slices; sliceNum++)
	{
		// Add the position
		vertPositions.push_back(position);

		// Add the indices for the triangle
		indices.push_back(0);
		indices.push_back(sliceNum + 1);
		indices.push_back((sliceNum + 1) % slices + 1);

		// Apply the rotation for the next position
		position = Maths::Matrix4x4::Transform(sliceRotation, position);
	}

	// Add the centre of the bottom of the cone
	position = Maths::Vector3(0, -height, 0);
	vertPositions.push_back(position);

	// Add the indices
	for (unsigned int sliceNum = 0; sliceNum < slices; sliceNum++)
	{
		indices.push_back(sliceNum + 1);
		indices.push_back(vertPositions.size() - 1);
		indices.push_back((sliceNum + 1) % slices + 1);
	}

	std::vector<Vertex *> verts;
	std::vector<PosNormVertex *> pnVerts;
	std::vector<Face> faces;

	// Min and max points for the bounding volume
	Maths::Vector3 minPos;
	Maths::Vector3 maxPos;

	// Create the vertices
	for (unsigned int i = 0; i < vertPositions.size(); i++)
	{
		pnVerts.push_back(new PosNormVertex(vertPositions[i], Maths::Vector3(0,1,0)));
		verts.push_back(pnVerts[i]);

		// Update  the minimum and maximum positions
		if(vertPositions[i].x > maxPos.x) maxPos.x = vertPositions[i].x;
		if(vertPositions[i].y > maxPos.y) maxPos.y = vertPositions[i].y;
		if(vertPositions[i].z > maxPos.z) maxPos.z = vertPositions[i].z;

		if(vertPositions[i].x < minPos.x) minPos.x = vertPositions[i].x;
		if(vertPositions[i].y < minPos.y) minPos.y = vertPositions[i].y;
		if(vertPositions[i].z < minPos.z) minPos.z = vertPositions[i].z;
	}

	// Create faces and calculate normals
	for (unsigned int i = 0; i < indices.size() / 3; i++)
	{
		faces.push_back(Face(*pnVerts[indices[i * 3]], 
			*pnVerts[indices[i * 3 + 1]],
			*pnVerts[indices[i * 3 + 2]],
			pnVerts[indices[i * 3]]->GetPosition(), 
			pnVerts[indices[i * 3 + 1]]->GetPosition(),
			pnVerts[indices[i * 3 + 2]]->GetPosition()));

		faces[i].AssignNormals();
	}

	// Create the vertex buffer
	VertexBuffer vb(verts, indices);

	// Set the vertex buffer implementation bridge
	SetVBBridge(vb);
	vb.GenerateVertexBuffer();

	// Delete the gumpf in the vertex list
	for (unsigned int i = 0; i < verts.size(); i++) delete verts[i];

	Mesh * m = new Mesh("Cone", Maths::Matrix4x4(), vb, new Bounding::BoundingAABB(minPos, maxPos));

	SetRenderBridge(*m);

	return m;
}

Mesh * GeometryFactory::TexturedQuad(float width, float height, bool twoSided)
{
    std::vector<Maths::Vector3> vertexPositions;
    std::vector<Maths::Vector2> texCoords;
    std::vector<Maths::Vector3> normals;
    
    std::vector<Vertex*> vertices;
    std::vector<unsigned short> indices;
    
    // Add the four corners
    vertexPositions.push_back(Maths::Vector3(-width / 2.0f, height / 2.0f, 0.0f));
    vertexPositions.push_back(Maths::Vector3(-width / 2.0f, -height / 2.0f, 0.0f));
    vertexPositions.push_back(Maths::Vector3(width / 2.0f, -height / 2.0f, 0.0f));
    vertexPositions.push_back(Maths::Vector3(width / 2.0f, height / 2.0f, 0.0f));
    
    // Create tex coords
    texCoords.push_back(Maths::Vector2(0.0f, 1.0f));
    texCoords.push_back(Maths::Vector2(0.0f, 0.0f));
    texCoords.push_back(Maths::Vector2(1.0f, 0.0f));
    texCoords.push_back(Maths::Vector2(1.0f, 1.0f));
    
    // Create normals
    for (int i = 0; i < 4; ++i)
    {
        Maths::Vector3 normal(vertexPositions[i]);
        normal.Normalise();
        
        normals.push_back(normal);
    }
    
    // Create vertex objects
    for (unsigned int i = 0; i < vertexPositions.size(); ++i)
        vertices.push_back(new SimpleVertex(vertexPositions[i], texCoords[i], normals[i]));
    
    // Create indices
    indices.push_back(0);   indices.push_back(1);   indices.push_back(2);
    indices.push_back(2);   indices.push_back(3);   indices.push_back(0);
    
    VertexBuffer vb(vertices, indices);
    
    // Generate the vertex buffer
    SetVBBridge(vb);
    vb.GenerateVertexBuffer();
    
    // Create a new mesh object
    Mesh * m = new Mesh("Quad", Maths::Matrix4x4(), vb, new Bounding::BoundingAABB(vertexPositions[0], vertexPositions[2]));
    
    SetRenderBridge(*m);
    
    // Delete the vertex objects
    //for (int i = 0; i < vertices.size(); ++i) delete vertices[i];
    
    // Return it
    return m;
}



