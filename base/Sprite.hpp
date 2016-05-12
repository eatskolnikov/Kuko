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
    FloatRect GetPosition();
    void SetFrame( IntRect fr );
    IntRect GetFrame();
    void SetRotation( float angle );
    float GetRotation();
    bool IsClicked( int x, int y );
    void SetAlpha( Uint8 value );
    Uint8 GetAlpha();

    SDL_Texture*        texture;
    IntRect             frame;
    float               angle;
    FloatRect           position;
    bool                isFlipped;
};

}

#endif
