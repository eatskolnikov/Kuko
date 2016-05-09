// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_IMAGEMANAGER
#define _KUKO_IMAGEMANAGER

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>

#include "../base/Sprite.hpp"

namespace kuko
{

class ImageManager
{
    public:
    static void Setup();
    static void Cleanup();

    static void AddTexture( const std::string& id, const std::string& path );
    static void ClearTextures();
    static SDL_Texture* GetTexture( const std::string& key );
    static std::string GetTextureFile( const std::string& key );

    static void Draw( const Sprite& sprite );
    static void Draw( SDL_Texture* ptrTexture, int x, int y );
    static void Draw( const Sprite& sprite, float offsetX, float offsetY );
    static void Draw( const Sprite& sprite, float offsetX, float offsetY, float scale );

    static void DrawRectangle( kuko::FloatRect pos, int r, int g, int b );

    protected:
    static std::map<std::string, SDL_Texture*> m_textures;
    static std::map<std::string, std::string> m_filenames;
    static SDL_Texture* LoadFile( const std::string& path );
};

}

#endif
