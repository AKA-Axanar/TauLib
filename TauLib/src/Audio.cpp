#include "Audio.h"
#include "SDL_mixer.h"

using namespace std;

///
/// @file
/// Audio - music, sounds.
///

namespace Tau {  // to avoid conflict with other libraries

SDL_Shared<Mix_Music> LoadMusicFile(const string& filePath) {
    return Mix_LoadMUS(filePath.c_str());
}

// loops = -1 for infinite
// returns true on success
bool PlayMusic(SDL_Shared<Mix_Music> music, int loops) {
    int ret = Mix_PlayMusic(music, loops);

    return ret == 0;
}

SDL_Shared<Mix_Chunk> LoadSoundFile(const string& filePath) {
    return Mix_LoadWAV(filePath.c_str());
}

// channel = -1 is next available channel
// loops = 0 is play once (loops is the number of additional loops)
// return is the channel the sound is on.  or -1 if error.
int PlaySound(SDL_Shared<Mix_Chunk> sound, int channel, int loops) {
    int channelOrError = Mix_PlayChannel(channel, sound, loops);

    return channelOrError;
}

} // end namespace Tau