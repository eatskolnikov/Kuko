// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "UILabel.hpp"

#include "../base/Application.hpp"
#include "../managers/ImageManager.hpp"

namespace kuko
{

void UILabel::Setup( const std::string& id, const std::string& label, SDL_Rect position, SDL_Color textColor, TTF_Font* font )
{
    m_position = position;
    m_color = textColor;
    m_font = font;
    m_label = label;
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
    SDL_Surface* textSurface = TTF_RenderText_Solid( m_font, m_label.c_str(), m_color );
    m_sprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), textSurface ) );
    m_sprite.position = m_position;

    SDL_FreeSurface( textSurface );
}

void UILabel::Draw()
{
//    Logger::Out( "Label " + m_id + " Color: " +
//        Logger::IntToString( m_color.r ) + "," +
//        Logger::IntToString( m_color.g ) + "," +
//        Logger::IntToString( m_color.b ) + "," +
//        Logger::IntToString( m_color.a ) );

    kuko::ImageManager::Draw( m_sprite );
}

}
