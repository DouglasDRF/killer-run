#pragma once

#include "Core.h"


class Sound {

public:
	static void PlayAudio(Mix_Chunk* sfx, int channel, int loops);
	
};