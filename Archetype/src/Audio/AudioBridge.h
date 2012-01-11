#pragma once

#include "libPrefix.h"


namespace AT
{

class AudioBridge
{

public:

	DLLEXPORT AudioBridge(void);

	DLLEXPORT virtual ~AudioBridge(void);

	DLLEXPORT virtual void SetupAudioEngine() = 0;
};

}