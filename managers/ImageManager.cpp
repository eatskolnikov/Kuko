// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "ImageManager.hpp"

#include "../base/Application.hpp"

namespace kuko
{

std::map<std::string, SDL_Texture*> ImageManager::m_textures;

void ImageManager::Setup()
{
    Logger::Out( "ImageManager::Setup" );
    AddImages();
}

void ImageManager::AddImages()
{
    Logger::Out( "ImageManager::AddImages" );
    // Load images that will be used
    //m_textures.insert( std::pair<std::string, SDL_Texture*>( "donaldo", LoadFile( "content/graphics/donaldo.png" ) ) );
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

}