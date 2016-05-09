// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "ImageManager.hpp"

#include "../base/Application.hpp"

namespace kuko
{

std::map<std::string, SDL_Texture*> ImageManager::m_textures;
std::map<std::string, std::string> ImageManager::m_filenames;

void ImageManager::AddTexture( const std::string& id, const std::string& path )
{
    m_filenames.insert( std::pair<std::string, std::string>( id, path ) );
    m_textures.insert( std::pair<std::string, SDL_Texture*>( id, LoadFile( path ) ) );
}

void ImageManager::ClearTextures()
{
    m_textures.clear();
    m_filenames.clear();
}

SDL_Texture* ImageManager::LoadFile( const std::string& path )
{
    SDL_Surface* loaded = IMG_Load( path.c_str() );
    if ( loaded == NULL )
    {
        Logger::Error( "Error loading image \"" + path + "\"" );
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( Application::GetRenderer(), loaded );
    if ( texture == NULL )
    {
        Logger::Error( "Error optimizing image \"" + path + "\"", "ImageManager::LoadFile" );
    }

    SDL_FreeSurface( loaded );
    return texture;
}

SDL_Texture* ImageManager::GetTexture( const std::string& key )
{
    if ( m_textures[ key ] == NULL )
    {
        Logger::Error( "Error - could not find image \"" + key + "\"", "ImageManager::GetTexture" );
    }
    return m_textures[ key ];
}

std::string ImageManager::GetTextureFile( const std::string& key )
{
    if ( m_filenames[ key ] == "" )
    {
        Logger::Error( "Error - could not find image \"" + key + "\"", "ImageManager::GetTextureFile" );
    }
    return m_filenames[ key ];
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

void ImageManager::Draw( const Sprite& sprite, float offsetX, float offsetY )
{
    Sprite offsetSprite = sprite;
    offsetSprite.position.x += offsetX;
    offsetSprite.position.y += offsetY;

    Draw( offsetSprite );
}

void ImageManager::Draw( const Sprite& sprite, float offsetX, float offsetY, float scale )
{
    Sprite offsetSprite = sprite;
    offsetSprite.position.x += offsetX;
    offsetSprite.position.y += offsetY;
    offsetSprite.position.w = sprite.position.w * scale;
    offsetSprite.position.h = sprite.position.h * scale;

    Draw( offsetSprite );
}

void ImageManager::Draw( const Sprite& sprite )
{
    SDL_RendererFlip flip = ( sprite.isFlipped ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_Rect rect = sprite.position.ToSDLRect();
    SDL_Rect frame = sprite.frame.ToSDLRect();

    SDL_RenderCopyEx(
        kuko::Application::GetRenderer(),
        sprite.texture,
        &frame,
        &rect,
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

void ImageManager::DrawRectangle( kuko::FloatRect pos, int r, int g, int b )
{
    SDL_Rect rect = pos.ToSDLRect();
    SDL_SetRenderDrawColor( Application::GetRenderer(), r, g, b, 255 );
    SDL_RenderDrawRect( Application::GetRenderer(), &rect );
}

}
