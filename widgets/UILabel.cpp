// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "UILabel.hpp"

#include "../base/Application.hpp"
#include "../managers/ImageManager.hpp"

namespace kuko
{

void UILabel::Setup( const std::string& id, const std::string& label, SDL_Rect position, bool centered, SDL_Color textColor, TTF_Font* font )
{
    Logger::Out( "Setup " + label + ", Centered " + I2S( centered ), "UILabel::Setup" );
    m_position = position;
    m_color = textColor;
    m_font = font;
    m_label = label;
    m_centered = centered;
    GenerateTexture();
}

void UILabel::ChangeText( const std::string& text )
{
    m_label = text;
    GenerateTexture();
}

void UILabel::SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    m_color.a = a;
}

void UILabel::GenerateTexture()
{
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( m_font, m_label.c_str(), m_color );
    m_sprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), textSurface ) );

    // Set w/h to fit the ratio
    int fullWidth, fullHeight;
    SDL_QueryTexture(m_sprite.texture, NULL, NULL, &fullWidth, &fullHeight);

    float fontRatio = float(fullWidth) / float(fullHeight);

    m_position.w = m_position.h * fontRatio;
    // Don't go off-screen (adjust width)
    if ( m_position.w > kuko::Application::GetScreenWidth() )
    {
        m_position.w = kuko::Application::GetScreenWidth() - 10;
    }
    // Don't go off-screen (adjust x)
    if ( m_position.x + m_position.w > kuko::Application::GetScreenWidth() )
    {
        m_position.x = kuko::Application::GetScreenWidth() - m_position.w - 5;
    }

    if ( m_centered )
    {
        m_position.x = ( kuko::Application::GetScreenWidth() / 2 ) - ( m_position.w / 2 );
    }
    m_sprite.position = m_position;

    SDL_FreeSurface( textSurface );
}

void UILabel::Draw()
{
    kuko::ImageManager::Draw( m_sprite );
}

}
