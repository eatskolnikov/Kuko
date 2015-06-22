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

bool Sprite::IsClicked( int x, int y )
{
    return ( position.x <= x && position.x + position.w > x && position.y <= y && position.y + position.h > y );
}

void Sprite::SetPosition( kuko::PositionRect pos )
{
    position.x = int(pos.x);
    position.y = int(pos.y);
    position.w = int(pos.w);
    position.h = int(pos.h);
}

void Sprite::SetFrame( SDL_Rect fr )
{
    frame = fr;
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
}

}
