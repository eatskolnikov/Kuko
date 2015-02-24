// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "ImageManager.hpp"

#include "../base/Application.hpp"

namespace kuko
{

std::map<std::string, SDL_Texture*> ImageManager::m_textures;

void ImageManager::Setup()
{
    Logger::Out( "ImageManager::Setup" );
}

void ImageManager::AddTexture( const std::string& id, const std::string& path )
{
    Logger::Out( "Add image " + id + " from path " + path, "ImageManager::AddTexture" );
    m_textures.insert( std::pair<std::string, SDL_Texture*>( id, LoadFile( path ) ) );
}

void ImageManager::ClearTextures()
{
    m_textures.clear();
}

SDL_Texture* ImageManager::LoadFile( const std::string& path )
{
    Logger::Out( "Load image \"" + path + "\"", "ImageManager::LoadFile" );
    SDL_Surface* loaded = IMG_Load( path.c_str() );
    if ( loaded == NULL )
    {
        Logger::Error( "Error loading image \"" + path + "\"" );
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( Application::GetRenderer(), loaded );
    if ( texture == NULL )
    {
        Logger::Error( "Error optimizing image \"" + path + "\"" );
    }

    SDL_FreeSurface( loaded );
    return texture;
}

SDL_Texture* ImageManager::GetTexture( const std::string& key )
{
    if ( m_textures[ key ] == NULL )
    {
        Logger::Error( "Error - could not find image \"" + key + "\"" );
    }
    return m_textures[ key ];
}

void ImageManager::Cleanup()
{
    for (   std::map<std::string, SDL_Texture*>::iterator it = m_textures.begin();
            it != m_textures.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            SDL_DestroyTexture( it->second );
            it->second = NULL;
        }
    }
}

void ImageManager::Draw( const Sprite& sprite )
{
    SDL_RendererFlip flip = ( sprite.isFlipped ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderCopyEx(
        kuko::Application::GetRenderer(),
        sprite.texture,
        &sprite.frame,
        &sprite.position,
        sprite.angle,
        NULL,
        flip
    );
}

void ImageManager::Draw( SDL_Texture* ptrTexture, int x, int y )
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = 200;
    pos.h = 50;

    SDL_RenderCopyEx(
        kuko::Application::GetRenderer(),
        ptrTexture,
        NULL,
        &pos,
        0.0f,
        NULL,
        SDL_FLIP_NONE
    );
}

}
