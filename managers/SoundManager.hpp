// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_SOUNDMANAGER
#define _KUKO_SOUNDMANAGER

#include <SDL.h>

#include <SDL_mixer.h>

#include <map>
#include <string>

namespace kuko
{

class SoundManager
{
    public:
    static void Cleanup();

    static void AddMusic( const std::string& id, const std::string& path );
    static void AddSound( const std::string& id, const std::string& path );
    static void ClearAudio();

    static void PlayMusic( const std::string& key, bool loop );
    static void PlaySound( const std::string& key );

    static void SetMusicVolume( int value );
    static void SetSoundVolume( int value );

    protected:
    static std::map<std::string, Mix_Chunk*> m_sounds;
    static std::map<std::string, Mix_Music*> m_music;

    static Mix_Chunk* LoadSoundFile( const std::string& path );
    static Mix_Music* LoadMusicFile( const std::string& path );

    static int m_musicVolume;
    static int m_soundVolume;
};

}

#endif
