// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Sprite.hpp"

#include "../base/Application.hpp"
#include "../utilities/StringUtil.hpp"
#include "../managers/ImageManager.hpp"

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

Sprite::~Sprite()
{
//    SDL_DestroyTexture( texture ); // Should be handled by the image manager!
    texture = NULL;
}

bool Sprite::IsClicked( int x, int y )
{
    return ( position.x <= x && position.x + position.w > x && position.y <= y && position.y + position.h > y );
}

void Sprite::SetPosition( kuko::FloatRect pos )
{
    position.x = pos.x;
    position.y = pos.y;
    position.w = pos.w;
    position.h = pos.h;
}

FloatRect Sprite::GetPosition()
{
    return position;
}

void Sprite::SetFrame( IntRect fr )
{
    frame = fr;
}

IntRect Sprite::GetFrame()
{
    return frame;
}

void Sprite::SetRotation( float angle )
{
    this->angle = angle;
}

float Sprite::GetRotation()
{
    return angle;
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

void Sprite::SetAlpha( Uint8 value )
{
    SDL_SetTextureAlphaMod( texture, value );
}

Uint8 Sprite::GetAlpha()
{
    Uint8 alpha;
    SDL_GetTextureAlphaMod( texture, &alpha );
    return alpha;
}

void Sprite::Draw()
{
    SDL_Rect rectPos = position.ToSDLRect();
    SDL_Rect rectFrame = frame.ToSDLRect();
    SDL_RendererFlip flipped = ( isFlipped ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    ImageManager::Draw( texture, &rectPos, &rectFrame, flipped, angle );
}

void Sprite::Draw( const kuko::IntRect& offset )
{
//    Logger::Out( "Draw B" );
//    Sprite temp = *this;
//    ImageManager::Draw( temp );
//    m_altTexture = texture;
//    ImageManager::Draw( m_altTexture, offset.ToSDLRect() );
}

}
