#pragma once

#include "libPrefix.h"

#include <string>
#include <set>



namespace AT
{
    // Forward declarations of maths classes so we don't have to #include them
    namespace Maths
    {
        class Vector2;
        class Vector3;
        class Matrix4x4;
        class Matrix3x3;
    }
    
namespace Model
{
    
    class Colour;
    
typedef std::set<std::string> AttrDescription;

class ShaderEffect
{
protected:

#pragma region Members


#pragma endregion

public:

#pragma region Constructors

	DLLEXPORT ShaderEffect();

#pragma endregion

#pragma region Destructor

	DLLEXPORT virtual ~ShaderEffect();

#pragma endregion

#pragma region Shader specific methods to Implement

	// Compile and link shader programs, or just prepare them for use
	DLLEXPORT virtual void GenerateShaderProgram() = 0;

	// Make the shader the active program
	DLLEXPORT virtual void MakeActive() const = 0;

#pragma endregion
    
#pragma region Getters and Setters
    
    DLLEXPORT virtual unsigned int GetProgramHandle() const = 0;
    
    virtual void AddAttribute(const std::string & attributeName) = 0;
    
    virtual int GetAttributeHandle(const std::string & attributeName) const = 0;
    
    virtual void AddUniform(const std::string & uniformName) = 0;
    
    virtual int GetUniformHandle(const std::string & uniformName) const = 0;
    
#pragma endregion
    
#pragma region Parameter Setting Methods
    
    DLLEXPORT virtual void SetParameter(const std::string & paramName, const Maths::Vector2 & vec2Parameter) = 0;
    DLLEXPORT virtual void SetParameter(const std::string & paramName, const Maths::Vector3 & vec3Parameter) = 0;
    DLLEXPORT virtual void SetParameter(const std::string & paramName, const Maths::Matrix4x4 & mat4Parameter) = 0;
    DLLEXPORT virtual void SetParameter(const std::string & paramName, const Maths::Matrix3x3 & mat3Parameter) = 0;
    DLLEXPORT virtual void SetParameter(const std::string & paramName, float floatParameter) = 0;
    
    DLLEXPORT virtual void SetParameter(const std::string & paramName, const Colour & colourParameter) = 0;
    
#pragma endregion
    
    

#pragma region Cloning methods

	DLLEXPORT virtual ShaderEffect * CreateNewObject() const = 0;

	DLLEXPORT virtual ShaderEffect * CloneThisObject() const = 0;

#pragma endregion

};

}
}