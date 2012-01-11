 
#include "StdAfx.h"

#include "Texture.h"

using namespace AT;
using namespace Model;

Texture * Texture::Prototype;

Texture::Texture()
{
}

Texture::Texture(const std::string & fileName)
: fileName(fileName)
{
}


Texture::~Texture()
{
}

void Texture::SetPrototype(Texture * prototype)
{
    // If a null ptr passed in, return
    if (!prototype) return;
    
    // If a prototype is already present, delete it
    if (Texture::Prototype)
        delete Texture::Prototype;
    
    Texture::Prototype = prototype;
}