///
/// @file
/// @brief CPP file for Audio routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "Audio.h"
#include "SDL_mixer.h"

using namespace std;

///
/// @file
/// @brief Audio - music, sounds.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

namespace Tau {  // to avoid conflict with other libraries

        //////////
        // Music
        //////////

//
// LoadMusicFile
//
Mix_Music* Audio::LoadMusicFile(const string& filePath) {
    return Mix_LoadMUS(filePath.c_str());
}

// loops = -1 for infinite
// returns true on success
bool Audio::PlayMusic(Mix_Music* music, int loops) {
    int ret = Mix_PlayMusic(music, loops);

    return ret == 0;    // 0 is success
}

        //////////
        // Sounds
        //////////

//
// LoadSoundFile
//
Mix_Chunk* Audio::LoadSoundFile(const string& filePath) {
    return Mix_LoadWAV(filePath.c_str());
}

//
// PlaySound
// channel = -1 is next available channel
// loops = 0 is play once (loops is the number of additional loops)
// return is the channel the sound is on.  or -1 if error.
//
int Audio::PlaySound(Mix_Chunk* sound, int channel, int loops) {
    int channelOrError = Mix_PlayChannel(channel, sound, loops);

    return channelOrError;
}

} // end namespace Tau