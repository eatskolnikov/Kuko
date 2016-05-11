// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "UIImage.hpp"

#include "../managers/ImageManager.hpp"
#include "../base/Application.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

UIImage::UIImage() : IWidget()
{
}

void UIImage::Setup( const std::string& id, FloatRect position, SDL_Texture* ptrTexture )
{
    m_position = position;

    if ( ptrTexture == NULL )
    {
        m_primitiveBackground = true;
        SetColor( { 0x00, 0xFF, 0xFF, 0xFF } );
    }
    else
    {
        m_background.SetTexture( ptrTexture );
        m_background.position = position;
        m_primitiveBackground = false;
    }
}

void UIImage::SetTexture( SDL_Texture* ptrTexture )
{
    FloatRect position = m_position;
    m_background.SetTexture( ptrTexture );
    m_background.position = position;
}

void UIImage::SetColor( SDL_Color color )
{
    m_color = color;
}

void UIImage::SetFrame( IntRect fr )
{
    m_background.SetFrame( fr );
}

IntRect UIImage::GetFrame()
{
    return m_background.GetFrame();
}

void UIImage::SetPosition( const IntRect& pos )
{
    IWidget::SetPosition( pos );
    m_background.SetPosition( m_position );
}

void UIImage::SetPosition( float x, float y, float w, float h )
{
    IWidget::SetPosition( x, y, w, h );
    m_background.SetPosition( m_position );
}

void UIImage::Update()
{
    float amountX = 0.05;
    float amountY = 0.025;
    if ( m_effect != "" )
    {
        m_effectTimer -= 1;
        if ( m_effectTimer <= 0 )
        {
            m_effectTimer = m_effectMax;
        }
    }

    if ( m_effect == "bob" )
    {
        if ( m_effectTimer > m_effectMax/2 )
        {
            m_position.x -= amountX / 2;
            m_position.y -= amountY / 2;
            m_position.w += amountX;
            m_position.h += amountY;
        }
        else
        {
            m_position.x += amountX / 2;
            m_position.y += amountY / 2;
            m_position.w -= amountX;
            m_position.h -= amountY;
        }

        m_background.position = m_position;
    }
    else if ( m_effect == "rotate" )
    {
        float angle = m_background.GetRotation();

        if ( m_effectTimer > m_effectMax/2 )
        {
            angle += 0.05;
        }
        else
        {
            angle -= 0.05;
        }

        m_background.SetRotation( angle );
    }
}

void UIImage::Draw()
{
    if ( m_primitiveBackground )
    {
        SDL_Rect rect = m_position.ToSDLRect();
        SDL_SetRenderDrawColor( Application::GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a );
        SDL_RenderFillRect( Application::GetRenderer(), &rect );
    }
    else
    {
        kuko::ImageManager::Draw( m_background );
    }
}

}
