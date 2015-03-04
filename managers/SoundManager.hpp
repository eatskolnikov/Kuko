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
    void Cleanup();

    void AddMusic( const std::string& id, const std::string& path );
    void AddSound( const std::string& id, const std::string& path );
    void ClearAudio();

    void PlayMusic( const std::string& key, bool loop );
    void PlaySound( const std::string& key );

    protected:
    std::map<std::string, Mix_Chunk*> m_sounds;
    std::map<std::string, Mix_Music*> m_music;

    Mix_Chunk* LoadSoundFile( const std::string& path );
    Mix_Music* LoadMusicFile( const std::string& path );
};

}

#endif
