#include "Sounds.h"

void Sound::PlayAudio(Mix_Chunk* sfx, int channel, int loops) {
	
	Mix_PlayChannel(channel, sfx, loops);
	
	if (Mix_Playing(channel) == 0) {
		Mix_FreeChunk(sfx);
	}
}
