// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "UILabel.hpp"

#include "../base/Application.hpp"
#include "../managers/ImageManager.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

UILabel::UILabel() : IWidget()
{
    m_useShadow = false;
}

void UILabel::Setup( const std::string& id, const std::string& label, SDL_Rect position, bool centered, SDL_Color textColor, TTF_Font* font, const std::string& effect, int effectMax )
{
    Logger::Out( "Setup " + label + ", Centered " + StringUtil::IntToString( centered ), "UILabel::Setup" );
    m_position = position;
    m_color = textColor;
    m_font = font;
    m_label = label;
    m_centered = centered;
    m_effect = effect;
    m_effectMax = effectMax;
    GenerateTexture();
}

void UILabel::Setup( const std::string& id, const std::string& label, SDL_Rect position, bool centered, SDL_Color textColor, TTF_Font* font, const std::string& effect, int effectMax, bool useShadow, SDL_Color shadowColor, int shadowOffsetX, int shadowOffsetY )
{
    m_shadowColor = shadowColor;
    m_useShadow = useShadow;
    m_shadowOffsetX = shadowOffsetX;
    m_shadowOffsetY = shadowOffsetY;
    Setup( id, label, position, centered, textColor, font, effect, effectMax );
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

void UILabel::SetShadowColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    m_shadowColor.r = r;
    m_shadowColor.g = g;
    m_shadowColor.b = b;
    m_shadowColor.a = a;
}

void UILabel::GenerateTexture()
{
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( m_font, m_label.c_str(), m_color );
    m_sprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), textSurface ) );
    SDL_FreeSurface( textSurface );

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

    if ( m_useShadow )
    {
        SDL_Surface* shadowSurface = TTF_RenderUTF8_Solid( m_font, m_label.c_str(), m_shadowColor );
        m_shadowSprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), shadowSurface ) );
        m_shadowSprite.position = m_position;
        m_shadowSprite.position.x += m_shadowOffsetX;
        m_shadowSprite.position.y += m_shadowOffsetY;

        SDL_FreeSurface( shadowSurface );
    }
}

void UILabel::Update()
{
    m_effectTimer--;
    if ( m_effectTimer < 0 ) { m_effectTimer = m_effectMax; }
}

void UILabel::Draw()
{
    if ( ( m_effect == "" )
        || ( m_effect == "flash" && m_effectTimer < m_effectMax/2 ) )
    {
        if ( m_useShadow )
        {
            kuko::ImageManager::Draw( m_shadowSprite );
        }
        kuko::ImageManager::Draw( m_sprite );
    }
}

}
