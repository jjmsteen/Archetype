
#include "StdAfx.h" 
 

#include "Model3D.h"

using namespace AT;
using namespace Model;

Model3D::Model3D(const std::vector<Mesh *> & meshes, const std::vector<Material*> & materials)
{
	// Copy pointers only
	this->meshes.assign(meshes.begin(), meshes.end());
    
    // Copy material pointers too
    this->materials.assign(materials.begin(), materials.end());
}


Model3D::~Model3D()
{
    // Delete the meshes
    for (int i = 0; i < meshes.size(); ++i)
        delete meshes[i];
    
    // Delete the no longer used materials
	for (int i = 0; i < materials.size(); ++i)
		delete materials[i];
}
