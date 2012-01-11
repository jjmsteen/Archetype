#pragma once

#include "libPrefix.h"

#include <string>
#include <cstdio>

#include "Vector2.h"
#include "Vector3.h"
#include "VBBridge.h"
#include "RenderBridge.h"


namespace AT
{
namespace Model
{

// Forward declaration of the Texture class
class Texture;
    
struct PolyFace {
	unsigned short v1;
	unsigned short v2;
	unsigned short v3;
};

	// Forward declaration of the Model class so it can be returned
	class Model3D;
	class Mesh;
	class Material;
	class Colour;

class ModelLoader
{
public:

#pragma region Members

	bool GenerateTangentFrames;

	bool FlipNormals;

	bool FlipWinding;

protected:

	// Position in file 
	unsigned int position;

	RenderBridge * renderBridge;

	VBBridge * vbBridge;
    
    Maths::Vector3 maxPoint;
    Maths::Vector3 minPoint;

public:

#pragma endregion

#pragma region Constructor/Destructor

	DLLEXPORT ModelLoader(RenderBridge * renderBridge = 0, VBBridge * vbBridge = 0,
		bool generateTangentFrames = false, bool flipNormals = false, bool flipWinding = false);

	DLLEXPORT ~ModelLoader(void);

#pragma endregion
    
#pragma region Getters and Setters
    
    DLLEXPORT const Maths::Vector3 & GetMaxPoint() const { return maxPoint; }
    DLLEXPORT const Maths::Vector3 & GetMinPoint() const { return minPoint; }

	// Get the position in the file (for progress bar)
	DLLEXPORT unsigned int GetPosition() const { return position; }
    
#pragma endregion

#pragma region Model Loader Factory Methods

	DLLEXPORT Model3D * LoadModel(const std::string & fileName);

#pragma endregion

#pragma region Model Loader Private Methods

private:

	DLLEXPORT Mesh * ReadObjectChunk(FILE * file, long chunkLength, std::vector<Material*> & materials);
    
	DLLEXPORT Material * ReadMaterialChunk(FILE * file, unsigned int chunkLength);

	DLLEXPORT std::string ReadName(FILE * file, long chunkLength);
	DLLEXPORT std::string  ReadName(FILE * file);
    
	DLLEXPORT short ReadPercentage(FILE * file, long chunkLength);
    
	DLLEXPORT void ReadVertexPositionChunk(FILE * file, std::vector<Maths::Vector3> & vertices, 
		unsigned short chunkLength);

	DLLEXPORT void ReadTexCoordChunk(FILE * file, std::vector<Maths::Vector2> & texCoords, 
		unsigned short chunkLength);
    
	DLLEXPORT void ReadFaceChunk(FILE * file, std::vector<PolyFace> & faceMarkers);
    
    DLLEXPORT Material * ReadFaceMaterialChunk(FILE * file, long chunkLength, const std::vector<Material*> & materials);
    
	DLLEXPORT Maths::Matrix4x4 ReadTransformMatrix(FILE * file);
    
	DLLEXPORT Colour ReadColourChunk(FILE * file, long chunkLength);
    
    DLLEXPORT Texture * ReadTextureChunk(FILE * file, long chunkLength);

#pragma endregion


};

}
}

