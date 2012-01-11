#pragma once

#include "libPrefix.h"

#include <vector>
#include <utility>
#include <string>

namespace AT
{
namespace Model
{

class Vertex
{
public:

	// Methods to implement

	// Returns the length the vertex would be as an array
	DLLEXPORT virtual unsigned short GetArrayLength() const = 0;

	// Get the vertex as an array of floats - WARNING! MANAGE MEMORY!
	DLLEXPORT virtual float * GetVertexAsArray() = 0;

	DLLEXPORT virtual ~Vertex() {};
    
    // Returns a vector of pairs of strings with the name of the vertex components and the number of elements
    DLLEXPORT virtual std::vector<std::pair<std::string, unsigned short > > GetVertexDescription() const = 0;
};

}
}