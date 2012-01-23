
#include "stdafx.h" 

#include "Material.h"

using namespace AT;
using namespace Model;

//Material::Material()
//	: diffuseMap(0), normalMap(0), specularMap(0)
//{
//}

Material::Material(const std::string & name, Texture * diffuseMap, Texture * normalMap, Texture * specularMap,
		const Colour & ambient, const Colour & diffuse, const Colour & specular, float transparency,
		float shininess)
		: name(name), diffuseMap(diffuseMap), normalMap(normalMap), specularMap(specularMap),
		ambientColour(ambient), diffuseColour(diffuse), specularColour(specular),
		transparency(transparency), shininess(shininess)
{
}


Material::~Material(void)
{
	if (diffuseMap)
		delete diffuseMap;

	if (normalMap)
		delete normalMap;

	if (specularMap)
		delete specularMap;
}

#pragma region Copy Constructor / OAO

Material::Material(const Material & m)
{
	this->deepCopy(m);
}

Material & Material::operator= (const Material & m)
{
	this->deepCopy(m);

	return *this;
}

void Material::deepCopy(const Material & m)
{
	this->name = m.name;

	if (m.diffuseMap != 0)
		this->diffuseMap = m.diffuseMap->CloneThisObject();
	else
		this->diffuseMap = 0;

	if (m.normalMap != 0)
		this->normalMap = m.normalMap->CloneThisObject();
	else 
		this->normalMap = 0;

	if (m.specularMap != 0)
		this->specularMap = m.specularMap->CloneThisObject();
	else
		this->specularMap = 0;

	this->ambientColour = m.ambientColour;
	this->diffuseColour = m.diffuseColour;
	this->specularColour = m.specularColour;

	this->transparency = m.transparency;
	this->shininess = m.shininess;
}

#pragma endregion

std::string Material::GetName() const
{
	return name;
}

Texture const * Material::GetDiffuseMap() const
{
	return diffuseMap;
}

Texture const * Material::GetNormalMap() const
{
	return normalMap;
}

Texture const * Material::GetSpecularMap() const
{
	return specularMap;
}

Colour Material::GetAmbientColour() const { return ambientColour; }
Colour Material::GetDiffuseColour() const { return diffuseColour; }
Colour Material::GetSpecularColour() const { return specularColour; } 
float Material::GetShininess() const { return shininess; }
float Material::GetTransparency() const { return transparency; }





















