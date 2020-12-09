#pragma once
#include "TauLib.h"
#include "SDL_Shared.h"
#include <string>

///
/// @file
/// Audio - music, sounds.
///

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau {

// Note: you don't want the last shared_ptr to go out of scope and be destroyed while the music is playing
SDL_Shared<Mix_Music> LoadMusicFile(const std::string& filePath);

// loops = -1 for infinite
// returns true on success
bool PlayMusic(SDL_Shared<Mix_Music> music, int loops = -1);

// loops = -1 for infinite
// returns true on success
bool PlayMusic(const std::string& filePath, int loops = -1);

bool PauseMusic();
bool ResumeMusic();
bool HaltMusic();

// Note: you don't want the last shared_ptr to go out of scope and be destroyed while the sound is playing
SDL_Shared<Mix_Chunk> LoadSoundFile(const std::string& filePath);

// channel = -1 is next available channel
// loops = 0 is play once (loops is the number of additional loops)
// return is the channel the sound is on.  or -1 if error.
int PlaySound(SDL_Shared<Mix_Chunk>, int channel = -1, int loops = 0);

bool HaltSound();
} // end namespace Tau
