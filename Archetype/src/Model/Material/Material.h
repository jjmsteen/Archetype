#pragma once

#include "libPrefix.h"

#include <string>

#include "Colour.h"
#include "Texture.h"
#include "ModelLoader.h"

namespace AT
{
namespace Model
{

class Material
{
    friend class ModelLoader;
    
	std::string name;

	// Texture maps
	Texture * diffuseMap;
	Texture * normalMap;
	Texture * specularMap;

	// Colours
	Colour ambientColour;
	Colour diffuseColour;
	Colour specularColour;

	// Single value properties
	float transparency;
	float shininess;

public:

	DLLEXPORT Material(const std::string & name = std::string("Default Material"), Texture * diffuseMap = 0, Texture * normalMap = 0, Texture * specularMap = 0,
		const Colour & ambient = Colour(), const Colour & diffuse  = Colour(), const Colour & specular  = Colour(), float transparency = 0,
		float shininess = 100);

	DLLEXPORT ~Material(void);

#pragma region Copy Constructor / OAO

	DLLEXPORT Material(const Material & m);

	DLLEXPORT Material & operator= (const Material & m);

private: 
	DLLEXPORT void deepCopy(const Material & m);
public:

#pragma endregion

#pragma region Getters and Setters

	DLLEXPORT std::string GetName() const;

	DLLEXPORT Texture const * GetDiffuseMap() const;

	DLLEXPORT Texture const * GetNormalMap() const;

	DLLEXPORT Texture const * GetSpecularMap() const;

	DLLEXPORT Colour GetAmbientColour() const;
	DLLEXPORT Colour GetDiffuseColour() const;
	DLLEXPORT Colour GetSpecularColour() const;
    
    DLLEXPORT float GetShininess() const;
    DLLEXPORT float GetTransparency() const;


#pragma endregion

};

}
}
