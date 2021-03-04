#pragma once
#include "TauLib.h"
#include <string>

///
/// @file
/// @brief Audio - music, sounds.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau {

/// @struct Audio
struct Audio {
            //////////
            // Music
            //////////

    ///
    /// @brief load a music file 
    /// @param filePath the filename of the mp3 music file
    /// 
    static Mix_Music* LoadMusicFile(const std::string& filePath);

    ///
    /// @brief Play a previously loaded music file
    /// @param music previous loaded music file
    /// @param loops = -1 for infinite
    /// @return true on success
    /// @note call LoadMusicFile(filePath) to load the music parameter
    /// 
   static  bool PlayMusic(Mix_Music* music, int loops = -1);

    /// @brief Pause music.
    /// @param channel.  -1 pasues all channels.
    static inline void PauseMusic(int channel) { Mix_Pause(channel); }

    ///
    /// @brief Resume music
    /// @param none
    /// @return none
    /// 
    static inline void ResumeMusic() { Mix_ResumeMusic(); } 

    ///
    /// @brief Halt music
    /// @param none
    /// @return none
    /// 
    static inline void HaltMusic() { Mix_HaltMusic(); }     

            //////////
            // Sounds
            //////////

    ///
    /// @brief load a sound file 
    /// @param filePath the filename of the sound file
    /// 
    static Mix_Chunk* LoadSoundFile(const std::string& filePath);

    ///
    /// @brief AllocateSoundChannels
    /// @param numChannels 
    /// @return the number of channels allocated
    /// 
    static inline int AllocateSoundChannels(int numChannels) { return Mix_AllocateChannels(numChannels); }

    ///
    /// @brief Play a previously loaded sound file
    /// @param sound previous loaded sound file
    /// @param channel. -1 is next available channel
    /// @param loops.  0 is play once (loops is the number of additional loops.  1 is 2 loops etc.)
    /// @return the channel the sound is on.  or returns -1 if error.
    /// @note call LoadSoundFile(filePath) to load the sound parameter
    /// 
    static int PlaySound(Mix_Chunk* sound, int channel = -1, int loops = 0);

    ///
    /// @brief halt a sound channel.  
    /// @param channel to halt.  -1 to halt all channels
    /// @return none
    ///
    static inline void HaltSoundChannel(int channel) { Mix_HaltChannel(channel); }

    ///
    /// @brief halt all sound channels.
    /// @return none
    ///
    static inline void HaltAllSoundChannels() { Mix_HaltChannel(-1); }
};

} // end namespace Tau
