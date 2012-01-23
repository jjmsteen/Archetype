 
#include "stdafx.h" 

#include "ModelLoader.h"

#include "3DSFileFlags.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "SimpleVertex.h"
#include "Model3D.h"
#include "Mesh.h"
#include "Face.h"
#include "Colour.h"
#include "Material.h"
#include "BoundingAABB.h"

#include <cstdio>
#ifdef WIN32
#include <io.h>
#endif

using namespace AT;
using namespace Model;

// Forward declarations
//Mesh * ReadObjectChunk(FILE * file, long chunkLength, std::vector<Material*> & materials);
//Material * ReadMaterialChunk(FILE * file, unsigned int chunkLength);


ModelLoader::ModelLoader(RenderBridge * renderBridge, VBBridge * vbBridge,
		bool generateTangentFrames, bool flipNormals, bool flipWinding)
		: renderBridge(renderBridge), vbBridge(vbBridge), GenerateTangentFrames(generateTangentFrames),
		FlipNormals(flipNormals), FlipWinding(flipWinding), maxPoint(), minPoint()
{
}


ModelLoader::~ModelLoader(void)
{
	if (renderBridge)
		delete renderBridge;

	if (vbBridge)
		delete vbBridge;

}


Model3D * ModelLoader::LoadModel(const std::string & fileName)
{
	// Create a new model class to return
	Model3D * m;

	std::vector<Material*> materials;
	std::vector<Mesh*> meshes;

	// Create a pointer to the file
	FILE * file3ds;

	// 2 byte hex number that contains teh chunk ID
	unsigned short l_chunk_id;

	// 4 byte number specifying the chunk length
	unsigned int l_chunk_length;

	// quantity of the information read
	//unsigned short l_qty;
    
    // Size of the file
    long lSize;

	// Open the file stream in binary mode and check whether it has succeeded
	if ( (file3ds = fopen(fileName.c_str(), "rb")) == NULL)
		return 0;

	// While the file pointer position is less than the file length
//#ifdef WIN32
	//while (ftell(file3ds) < _filelength( fileno(file3ds) ) )
//#else
        //int result = feof(file3ds);
    
    // Debug var
    position = 0;
    
    fseek(file3ds, 0, SEEK_END);
    
    lSize = ftell(file3ds);
    
    rewind(file3ds);
    
    while (ftell(file3ds) <= lSize)
//#endif
	{
		// Read the chunk ID
		fread(&l_chunk_id, sizeof(unsigned short), 1, file3ds);
		
		// Read the length of this chunk
		fread(&l_chunk_length, sizeof(unsigned int), 1, file3ds);
        
        position = ftell(file3ds);

		switch (l_chunk_id)
		{
		case MAIN_CHUNK :
			
			break;

		case EDITOR_3D:
			
			break;

		case MATERIAL_BLOCK:
			
			materials.push_back(ReadMaterialChunk(file3ds, l_chunk_length));

			break;

		case OBJECT_BLOCK:
			
			meshes.push_back(ReadObjectChunk(file3ds, l_chunk_length, materials));

			break;

		default:
			fseek(file3ds, l_chunk_length - 6, SEEK_CUR);

			break;
		}
	}
    
    // Close the file read
    fclose(file3ds);

	m = new Model3D(meshes, materials);

	// Load textures
	for (int i = 0; i < materials.size(); i++)
	{
        if (materials[i]->diffuseMap)
            materials[i]->diffuseMap->LoadTexture();
	}

	return m;
}


std::string  ModelLoader::ReadName(FILE * file, long chunkLength)
{
	// Get the file position
	long pos = ftell(file);

	long endOfChunk = pos + chunkLength - 6;

	// Char for reading names, not set to zero as this is a null termintor
	char l_char = 99;

	std::string name;

	// While the char placeholder does not equal the null terminator
	while (/*l_char != '\0' && */(pos < endOfChunk))
	{
		// Read in the next char value
		fread(&l_char, sizeof(char), 1, file);

		// Add it to the name string
		name += l_char;

		pos = ftell(file);
	}

	return name;
}

std::string  ModelLoader::ReadName(FILE * file)
{
	// Char for reading names, not set to zero as this is a null termintor
	char l_char = 99;

	std::string name;

	// While the char placeholder does not equal the null terminator
	while (l_char != '\0')
	{
		// Read in the next char value
		fread(&l_char, sizeof(char), 1, file);

		// Add it to the name string
		name += l_char;
	}

	return name;
}

 short  ModelLoader::ReadPercentage(FILE * file, long chunkLength)
{
	// The initial position of the file
	long initialPosition = ftell(file);

	// Header and length values
	unsigned short l_chunk_id;
	unsigned int l_chunk_length;

	// Placeholder to return
	short perc = 0;

	// While the file position is before the end of the chunk
	while (ftell(file) < (initialPosition + chunkLength - 6))
	{
		// Read in the chunk header and length
		fread(&l_chunk_id, sizeof(l_chunk_id), 1, file);
		fread(&l_chunk_length, sizeof(l_chunk_length), 1, file);

		// If the chunk is a percentage chunk
		if (l_chunk_id == PERCENTAGE)
		{
			// Read it in
			fread(&perc, sizeof(short), 1, file);
		}
		else
		{
			// Otherwise go to the end of that chunk
			fseek(file, l_chunk_length - 6, SEEK_CUR);
		}
	}

	return perc;
}

 void  ModelLoader::ReadVertexPositionChunk(FILE * file, std::vector<Maths::Vector3> & vertices, 
	 unsigned short chunkLength)
{
	// short value for reading info about the chunk
	unsigned short l_qty;

	Maths::Vector3 vpos(0,0,0);

	// Read the quantity of the vertices
	fread(&l_qty, sizeof(unsigned short), 1, file);
    
    // Temporary y for swizzling
    //float tempY;

	for (int i = 0; i < l_qty; i++)
	{
		// Read the three position components, swapping z and y
		fread(&vpos.x, sizeof(float), 1, file);
		fread(&vpos.z, sizeof(float), 1, file);
		fread(&vpos.y, sizeof(float), 1, file);
        
        // Negate the y component (which was z in 3ds file)
        vpos.z = -(vpos.z);
        
//        tempY = vpos.y;
//        
//        vpos.y = -(vpos.z);
//        
//        vpos.z = tempY;
        
		// Put it in the passed list
		vertices.push_back(vpos);
	}
}

 void ModelLoader::ReadTexCoordChunk(FILE * file, std::vector<Maths::Vector2> & texCoords, 
	 unsigned short chunkLength)
{
	// short value for reading info about the chunk
	unsigned short l_qty;

	// Create a texCoord placeholder
	Maths::Vector2 tc;

	// Read the quantity of texCoords
	fread(&l_qty, sizeof(unsigned short), 1, file);

	for (int i = 0; i < l_qty; i++)
	{
		// Read the u and v components
		fread(&tc.x, sizeof(float), 1, file);
		fread(&tc.y, sizeof(float), 1, file);

		// Put it in the passed list
		texCoords.push_back(tc);
	}
}

 void ModelLoader::ReadFaceChunk(FILE * file, std::vector<PolyFace> & faceMarkers)
{
	// A placeholder face description
	PolyFace p;

	// A placeholder for the face flags (unused)
	unsigned short l_face_flags;

	// Read the number of faces
	unsigned short l_qty;
	fread(&l_qty, sizeof(unsigned short), 1, file);

	for (int i = 0; i < l_qty; ++i)
	{
		// Read the face indices
		fread(&p.v1, sizeof(unsigned short), 1, file);
		fread(&p.v2, sizeof(unsigned short), 1, file);
		fread(&p.v3, sizeof(unsigned short), 1, file);
		fread(&l_face_flags, sizeof(unsigned short), 1, file);

		// Put the new face in the list
		faceMarkers.push_back(p);
	}
}

Material * ModelLoader::ReadFaceMaterialChunk(FILE * file, long chunkLength, const std::vector<Material*> & materials)
{
    // Find the initial position and setup a current position var
    long initialPos = ftell(file);
    long pos = initialPos;
    
    // Calculate the end of the chunk
    long endOfChunk = initialPos + chunkLength - 6;
    
    // Set up the subchunk reader vars
    //unsigned short l_chunk_id = 0;
    //unsigned int l_chunk_length = 0;
    
    std::string name = ReadName(file);
    
    return 0;
}

 Maths::Matrix4x4 ModelLoader::ReadTransformMatrix(FILE * file)
{
	// Create a placeholder array (X:0-2, Y:3-5, Z:6-8, Translation:9-11)
    float matrix[12];
    
    for (int i = 0; i < 12; ++i)
    {
        fread(&matrix[i], sizeof(float), 1, file);
    }
    
//    return Maths::Matrix4x4(matrix[0], matrix[3], matrix[6], matrix[9],
//                            matrix[1], matrix[4], matrix[7], matrix[10],
//                            matrix[2], matrix[5], matrix[8], matrix[11],
//                            0,         0,         0,         1);
    
    return Maths::Matrix4x4();

}

Mesh * ModelLoader::ReadObjectChunk(FILE * file, long chunkLength, std::vector<Material*> & materials)
{
	// Get the initial position of the file pointer
	long initialPosition = ftell(file);

	// 2 byte hex number that contains teh chunk ID
	unsigned short l_chunk_id;

	// 4 byte number specifying chunk length
	unsigned int l_chunk_length;

	// Mesh specific lists
	std::vector<Maths::Vector3> vertPositions;
	std::vector<Maths::Vector2> texCoords;
	std::vector<PolyFace> faces;
	std::vector<SimpleVertex *> vertices;
	std::vector<Material*> meshMaterials;

	// Mesh specific objects
	std::string materialName;
	Maths::Matrix4x4 world;

	Mesh * m;

	// First things first, read in the name
	std::string meshName = ReadName(file);

	// While the read position is before the end of the object chunk, removing the header
	while(ftell(file) < (initialPosition + chunkLength - 6))
	{
		// Read the chunk id and length
		fread(&l_chunk_id, sizeof(l_chunk_id), 1, file);
		fread(&l_chunk_length, sizeof(l_chunk_length), 1, file);

		switch (l_chunk_id)
		{

		case TRIANGULAR_MESH:			
			break;

		//case NAMED_OBJECT:

		//	meshName = ReadName(file, l_chunk_length);

		//	break;

		case VERTICES_LIST:

			ReadVertexPositionChunk(file, vertPositions, l_chunk_length);

			break;

		case MAPPING_COORDINATES_LIST:

			ReadTexCoordChunk(file, texCoords, l_chunk_length);

			break;

		case FACES_DESCRIPTION:

			ReadFaceChunk(file, faces);

			break;

		case FACES_MATERIAL:

			// Get the local current position
			//localPosition = ftell(file);
                
            //ReadFaceMaterialChunk(file, l_chunk_length, materials);

			fpos_t position;
			fgetpos(file, &position);

			// Get the name of the material
			materialName = ReadName(file);

			// Loop over the material input
			for (int i = 0; i < materials.size(); i++)
			{
				// If the name matches
				if (materialName == materials[i]->GetName())
				{
					// Add the materials to the list
					meshMaterials.push_back(materials[i]);
					break;
				}
			}

			fsetpos(file, &position);

			// Read to the end of the chunk
			fseek(file, l_chunk_length - 6, SEEK_CUR);

			break;

		case TRANSLATION_MATRIX:

			world = ReadTransformMatrix(file);

			break;

		default:

			// If the chunk header is unknown, go to the end of the chunk
			fseek(file, l_chunk_length - 6, SEEK_CUR);

			break;
		}

	}

	// Generate texture coordinates if none exist in the file
	if (texCoords.size() == 0)
	{
		for (int i = 0; i < vertPositions.size(); i++)
		{
			texCoords.push_back(Maths::Vector2());
		}
	}

	// The max and min vertex positions
	Maths::Vector3 maxPos;
	Maths::Vector3 minPos;

	// Create a list of vertices
	for (int i = 0; i < vertPositions.size(); i++)
	{
		vertices.push_back(
			new SimpleVertex(vertPositions[i], 
								texCoords[i], 
								Maths::Vector3(0,1,0))
							);

		// Update  the minimum and maximum positions
		if(vertPositions[i].x > maxPos.x) maxPos.x = vertPositions[i].x;
		if(vertPositions[i].y > maxPos.y) maxPos.y = vertPositions[i].y;
		if(vertPositions[i].z > maxPos.z) maxPos.z = vertPositions[i].z;

		if(vertPositions[i].x < minPos.x) minPos.x = vertPositions[i].x;
		if(vertPositions[i].y < minPos.y) minPos.y = vertPositions[i].y;
		if(vertPositions[i].z < minPos.z) minPos.z = vertPositions[i].z;
	}
    
    // Update the model loader's current max and min points
    if((maxPos.x + world.GetTranslation().x) > this->maxPoint.x) this->maxPoint.x = maxPos.x;
    if((maxPos.y + world.GetTranslation().y) > this->maxPoint.y) this->maxPoint.y = maxPos.y;
    if((maxPos.z + world.GetTranslation().z) > this->maxPoint.z) this->maxPoint.z = maxPos.z;
    
    if((minPos.x + world.GetTranslation().x) < this->minPoint.x) this->minPoint.x = minPos.x;
    if((minPos.y + world.GetTranslation().y) < this->minPoint.y) this->minPoint.y = minPos.y;
    if((minPos.z + world.GetTranslation().z) < this->minPoint.z) this->minPoint.z = minPos.z;

	// Create a list of faces to calculate normals
	std::vector<Face> normalFaces; 

	for (int i = 0; i < faces.size(); i++)
	{
		Face f = Face(*(vertices[faces[i].v1]), 
			*(vertices[faces[i].v2]), 
			*(vertices[faces[i].v3]),
			vertices[faces[i].v1]->GetPosition(),
			vertices[faces[i].v2]->GetPosition(),
			vertices[faces[i].v3]->GetPosition());
			
		normalFaces.push_back(f);
	}

	// Loop over the faces and calculate each vertex's normal
	for (int i = 0; i < normalFaces.size(); i++)
	{
		normalFaces[i].AssignNormals();
	}

	// Put the face indices into a list
	std::vector<unsigned short> indices;

	for (int i = 0; i < faces.size(); i++)
	{
		indices.push_back(faces[i].v1);
		indices.push_back(faces[i].v2);
		indices.push_back(faces[i].v3);
	}

	// Empty the vertex list into one that is compatible with a vertex buffer
	std::vector<Vertex *> vbVerts;

	// Assign from one vertex list to another with iterators
	vbVerts.assign(vertices.begin(), vertices.end());

	// Create the vertex buffer object
	VertexBuffer vb(vbVerts, indices);

	// Attach the bridge object if it exists
	if (vbBridge)
    {
		vb.SetBridge(vbBridge->CreateNewObject());
        
        // Generate a local representation of the vertex buffer
        vb.GenerateVertexBuffer();
    }

	// Free up some memory by deleting the now useless verts in the lists
	for (int i = 0; i < vertices.size(); i++)
	{
		delete vertices[i];
	}
    
    if (meshMaterials.size() > 0)
    {
        // Create the mesh object
        m = new Mesh(meshName, world, vb, new Bounding::BoundingAABB(minPos, maxPos, world.GetTranslation()), meshMaterials[0]);
    }
    else
    {
        // Create the mesh object
        m = new Mesh(meshName, world, vb, new Bounding::BoundingAABB(minPos, maxPos, world.GetTranslation()));
    }

	// Attach the render bridge if it exists
	if (renderBridge)
		m->SetRenderer(renderBridge->CreateNewObject());

	return m;
}

Colour ModelLoader::ReadColourChunk(FILE * file, long chunkLength)
{
	// Get the initial position of the file pointer
	long initialPosition = ftell(file);

	// 2 byte hex number that contains teh chunk ID
	unsigned short l_chunk_id;

	// 4 byte number specifying chunk length
	unsigned int l_chunk_length;

	// Create placeholder colour
	Colour c;

	while (ftell(file) < (initialPosition + chunkLength - 6))
	{
		fread(&l_chunk_id, sizeof(l_chunk_id), 1, file);
		fread(&l_chunk_length, sizeof(l_chunk_length), 1, file);

		if (l_chunk_id == RGB_COLOR)
		{
			unsigned char colourValue = 0;

			// Read and set the red value
			fread(&colourValue, sizeof(unsigned char), 1, file);
			c.SetRed(colourValue);

			// Read and set the green value
			fread(&colourValue, sizeof(unsigned char), 1, file);
			c.SetGreen(colourValue);

			// Read and set the blue value
			fread(&colourValue, sizeof(unsigned char), 1, file);
			c.SetBlue(colourValue);
		}
		else 
		{
			fseek(file, l_chunk_length - 6, SEEK_CUR);
		}

	}

	return c;
}


Texture * ModelLoader::ReadTextureChunk(FILE * file, long chunkLength)
{
    // Get the initial position of the file pointer
	long initialPosition = ftell(file);
    
	// 2 byte hex number that contains teh chunk ID
	unsigned short l_chunk_id = 0;
    
	// 4 byte number specifying chunk length
	unsigned int l_chunk_length = 0;
    
    // A string to read the filename into
    std::string filename;
    
    // A pointer to the texture object
    Texture * texture = 0;
    
    // Use pos as a debug variable
    long pos = initialPosition;
    
    long endOfChunk = initialPosition + chunkLength - 6;
    
    // While the read position is before the end of the material chunk
	while(ftell(file) < (initialPosition + chunkLength - 6))
	{
        // Read the chunk id and length
		fread(&l_chunk_id, sizeof(l_chunk_id), 1, file);
		fread(&l_chunk_length, sizeof(l_chunk_length), 1, file);
        
        switch (l_chunk_id) 
        {
            case MAPPING_FILENAME:
                
                // Read the file name
                filename = ReadName(file);
                
                break;
                
            default:
                
                // If the chunk header is unknown, go to the end of the chunk
                fseek(file, l_chunk_length - 6, SEEK_CUR);
                
                break;
		}
        
        pos = ftell(file);
        
    }
    
    // If there is a prototype object for textures
    if (Texture::Prototype)
    {
        // Create a clone of this subclass
        texture = Texture::Prototype->CreateNewObject();
        texture->SetFilename(filename);
    }
    
    return texture;
}

Material * ModelLoader::ReadMaterialChunk(FILE * file, unsigned int chunkLength)
{
	// Get the initial position of the file pointer
	long initialPosition = ftell(file);

	// 2 byte hex number that contains teh chunk ID
	unsigned short l_chunk_id = 0;

	// 4 byte number specifying chunk length
	unsigned int l_chunk_length = 0;

	// Placeholders for material variables
	std::string name, diffuseFileName, normalFileName, specFileName;
	Colour ambient, diffuse, specular;

	Texture * diffuseMap = 0;
	Texture * normalMap = 0;
	Texture * specMap = 0;

	float transparency = 0;
	float shininess = 0;
    
    unsigned int position = 0;

	// While the read position is before the end of the material chunk (removing the header length)
	while(ftell(file) < (initialPosition + chunkLength - 6))
	{
        
        position = ftell(file);
        
		// Read the chunk id and length
		fread(&l_chunk_id, sizeof(l_chunk_id), 1, file);
		fread(&l_chunk_length, sizeof(l_chunk_length), 1, file);

		switch(l_chunk_id)
		{

		case MATERIAL_NAME:

			name = ReadName(file, l_chunk_length);

			break;

		case AMBIENT_COLOR:

			ambient = ReadColourChunk(file, l_chunk_length);

			break;

		case DIFFUSE_COLOR:

			diffuse = ReadColourChunk(file, l_chunk_length);

			break;

		case SPECULAR_COLOR:

			specular = ReadColourChunk(file, l_chunk_length);

			break;

		case TEXTURE_MAP_1:
        case TEXTURE_MAP_2:
                
            diffuseMap = ReadTextureChunk(file, l_chunk_length);

			break;

		case BUMP_MAP:

            normalMap = ReadTextureChunk(file, l_chunk_length);
                

			break;

		case SPECULAR_MAP:
                
            specMap = ReadTextureChunk(file, l_chunk_length);

			break;

		case SHININESS:

			shininess = ReadPercentage(file, l_chunk_length);

			break;

		case TRANSPARENCY:

			transparency = ReadPercentage(file, l_chunk_length);

			break;

		default:

			// If the chunk header is unknown, go to the end of the chunk
			fseek(file, l_chunk_length - 6, SEEK_CUR);

			break;
		}
	}

	// Return a material object
	return new Material(name, diffuseMap, normalMap, specMap,
		ambient, diffuse, specular, transparency, shininess);

}