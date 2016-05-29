// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "SoundManager.hpp"

#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

std::map<std::string, Mix_Chunk*> SoundManager::m_sounds;
std::map<std::string, Mix_Music*> SoundManager::m_music;

void SoundManager::Cleanup()
{
    ClearAudio();
}

void SoundManager::AddMusic( const std::string& id, const std::string& path )
{
    Logger::Out( "Load music \"" + path + "\"", "SoundManager::AddMusic" );
    m_music.insert( std::pair< std::string, Mix_Music* >( id, LoadMusicFile( path ) ) );
}

void SoundManager::AddSound( const std::string& id, const std::string& path )
{
    Logger::Out( "Load sound \"" + path + "\"", "SoundManager::AddSound" );
    // TODO Possibly stores NULL, maybe fix this.
    m_sounds.insert( std::pair< std::string, Mix_Chunk* >( id, LoadSoundFile( path ) ) );
}

void SoundManager::ClearAudio()
{

    Logger::Out( "SoundManager::Cleanup" );

    for (   std::map<std::string, Mix_Chunk*>::iterator it = m_sounds.begin();
            it != m_sounds.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            Mix_FreeChunk( it->second );
            it->second = NULL;
        }
    }

    for (   std::map<std::string, Mix_Music*>::iterator it = m_music.begin();
            it != m_music.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            Mix_FreeMusic( it->second );
            it->second = NULL;
        }
    }
}

void SoundManager::PlayMusic( const std::string& key, bool loop )
{
//return;
    Logger::Out( "Play music ID: " + key, "SoundManager::PlayMusic" );

    if ( Mix_PlayingMusic() != 0 )
    {
        Mix_HaltMusic();
    }

    if ( m_music.find( key ) != m_music.end() )
    {
        // -1 = infinite, 0 = none, # = how many times to loop
        int loops = ( loop ) ? -1 : 1;
        Mix_FadeInMusicPos( m_music[ key ], loops, 2000, 0 );
    }
    else
    {
        Logger::Out( "Music \"" + key + "\" not found" );
    }
}

void SoundManager::PlaySound( const std::string& key )
{
    Logger::Out( "play sound " + key );
    if ( m_sounds.find( key ) != m_sounds.end() )
    {
        Logger::Out( "key found" );
        // int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops)
        Mix_PlayChannel( -1, m_sounds[ key ], 0 );
    }
}

Mix_Chunk* SoundManager::LoadSoundFile( const std::string& path )
{
    Mix_Chunk* sound = Mix_LoadWAV( path.c_str() );
    if( sound == NULL )
    {
        Logger::Error( "Error loading audio file \"" + path + "\": " + Mix_GetError() );
    }
    return sound;
}

Mix_Music* SoundManager::LoadMusicFile( const std::string& path )
{
    Mix_Music* music = Mix_LoadMUS( path.c_str() );
    if( music == NULL )
    {
        Logger::Error( "Error loading music file \"" + path + "\": " + Mix_GetError() );
    }
    return music;
}

}
