// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Sprite.hpp"

#include "../base/Application.hpp"

namespace kuko
{

Sprite::Sprite()
{
    texture = NULL;
    frame.x = frame.y = 0;
    frame.w = frame.h = 16;

    position.x = position.y = 0;
    position.w = position.h = 16;
    isFlipped = false;
    angle = 0.0f;
}

void Sprite::SetTexture( SDL_Texture* ptrTexture )
{
    texture = ptrTexture;//LoadFile( path );
    position.x = position.y = 0;
    frame.x = frame.y = 0;

    int w, h;
    SDL_QueryTexture( texture, NULL, NULL, &w, &h );
    position.w = frame.w = w;
    position.h = frame.h = h;
}

SDL_Texture* Sprite::GetTexture()
{
    return texture;
}

Sprite::~Sprite()
{
    if ( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
    }
}

}