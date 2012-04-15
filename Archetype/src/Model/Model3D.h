#pragma once

#include "libPrefix.h"

#include <vector>

#include "ModelLoader.h"
#include "Mesh.h"
#include "Material.h"

namespace AT
{
namespace Model
{

class Model3D
{

#pragma region Friend Classes

	friend class ModelLoader;

#pragma endregion

#pragma region Members

	// Meshes
	std::vector<Mesh*> meshes;
    
    // Materials
    std::vector<Material*> materials;

#pragma endregion

public:
	
#pragma region Constructors

	DLLEXPORT Model3D(const std::vector<Mesh *> & meshes, const std::vector<Material*> & materials);

#pragma endregion

#pragma region Destructors

	DLLEXPORT virtual ~Model3D();

#pragma endregion
    
#pragma region Getters and Setters
    
    DLLEXPORT const std::vector<Mesh*> & GetMeshes() const { return meshes; };

	DLLEXPORT const std::vector<Material*> & GetMaterials() const { return materials; }
    
#pragma endregion

#pragma region Member Functions


#pragma endregion


};

}
}