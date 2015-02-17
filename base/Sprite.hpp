// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _SPRITE
#define _SPRITE

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "../utilities/Logger.hpp"

namespace kuko
{

class Sprite
{
    public:
    Sprite();
    ~Sprite();

    void SetTexture( SDL_Texture* ptrTexture );
    SDL_Texture* GetTexture();

    SDL_Texture*    texture;
    SDL_Rect        frame;
    SDL_Rect        position;
    bool            isFlipped;
};

}

#endif
