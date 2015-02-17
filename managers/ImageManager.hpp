// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _IMAGEMANAGER
#define _IMAGEMANAGER

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

    static void AddImages();
    static SDL_Texture* GetTexture( const std::string& key );
    static SDL_Texture* LoadFile( const std::string& path );

    protected:
    static std::map<std::string, SDL_Texture*> m_textures;
};

}

#endif
