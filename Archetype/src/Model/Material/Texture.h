#pragma once

#include "libPrefix.h"

#include <string>

namespace AT
{
namespace Model
{

class Texture
{
public:

	static Texture * Prototype;

protected:

	// The name of the file to be loaded into a texture
	std::string fileName;

public:

	DLLEXPORT Texture();
    
    DLLEXPORT Texture(const std::string & fileName);

	DLLEXPORT static void SetPrototype(Texture * prototype);

	// Leave the texture loading to be platform specific
	DLLEXPORT virtual void LoadTexture(const std::string & fileName) = 0;
    DLLEXPORT virtual void LoadTexture() = 0;

	DLLEXPORT virtual void UnloadTexture() = 0;

	DLLEXPORT virtual ~Texture();

	DLLEXPORT virtual void MakeActive() const = 0;
    
    DLLEXPORT void SetFilename(const std::string & fileName) { this->fileName = fileName; }
    DLLEXPORT const std::string & GetFilename() { return this->fileName; }

#pragma region Cloning methods

	DLLEXPORT virtual Texture * CreateNewObject() const = 0;

	DLLEXPORT virtual Texture * CloneThisObject() const = 0;

#pragma endregion

};

}
}