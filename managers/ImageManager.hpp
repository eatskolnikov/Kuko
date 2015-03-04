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
    void Setup();
    void Cleanup();

    void AddTexture( const std::string& id, const std::string& path );
    void ClearTextures();
    SDL_Texture* GetTexture( const std::string& key );

    void Draw( const Sprite& sprite );
    void Draw( SDL_Texture* ptrTexture, int x, int y );

    protected:
    std::map<std::string, SDL_Texture*> m_textures;
    SDL_Texture* LoadFile( const std::string& path );
};

}

#endif
