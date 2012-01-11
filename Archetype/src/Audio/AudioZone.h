#pragma once

#include "libPrefix.h"

#include "Mesh.h"

namespace AT
{
namespace Audio
{

class AudioZone
{
protected:

	Model::Mesh zoneShape; 

public:

	AudioZone(const Model::Mesh & zoneShape);

	virtual ~AudioZone(void);

};

}
}