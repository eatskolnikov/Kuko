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
    void SetPosition( kuko::FloatRect pos );
    void SetFrame( IntRect fr );
    bool IsClicked( int x, int y );

    SDL_Texture*        texture;
    IntRect             frame;
    FloatRect           position;
    bool                isFlipped;
    float               angle;
};

}

#endif
