// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "UIImage.hpp"

#include "../managers/ImageManager.hpp"
#include "../base/Application.hpp"

namespace kuko
{

void UIImage::Setup( const std::string& id, SDL_Rect position, SDL_Texture* ptrTexture )
{
    Logger::Out( "Creating UIImage \"" + id + "\"", "UIImage::Setup" );
    m_position = position;

    if ( ptrTexture == NULL )
    {
        m_primitiveBackground = true;
        SetColor( 0x00, 0xFF, 0xFF, 0xFF );
    }
    else
    {
        m_background.SetTexture( ptrTexture );
        m_primitiveBackground = false;
    }
}

void UIImage::SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void UIImage::Draw()
{
    if ( m_primitiveBackground )
    {
        SDL_SetRenderDrawColor( Application::GetRenderer(), r, g, b, a );
        SDL_RenderFillRect( Application::GetRenderer(), &m_position );
    }
    else
    {
    }

    //kuko::ImageManager::Draw( background );
}

}
