// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_SPRITE
#define _KUKO_SPRITE

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "../utilities/Logger.hpp"
#include "PositionRect.hpp"

namespace kuko
{

class Sprite
{
    public:
    Sprite();
    ~Sprite();

    void SetTexture( SDL_Texture* ptrTexture );
    SDL_Texture* GetTexture();
    void SetPosition( kuko::PositionRect pos );

    SDL_Texture*        texture;
    SDL_Rect            frame;
    SDL_Rect            position;
    bool                isFlipped;
    float               angle;
};

}

#endif
