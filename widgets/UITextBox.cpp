#include "UITextBox.hpp"

#include "../base/Application.hpp"
#include "../managers/ImageManager.hpp"

namespace kuko
{

UITextBox::UITextBox()
{
    m_label = "text";
}

void UITextBox::Setup( const std::string& id, SDL_Rect position, SDL_Color bgColor, SDL_Color textColor, TTF_Font* font )
{
    Logger::Out( "Setup " + id, "UITextBox::Setup" );
    m_position = position;
    m_textColor = textColor;
    m_bgColor = bgColor;
    m_font = font;
    GenerateTexture();
}

void UITextBox::SetTextColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    m_textColor.r = r;
    m_textColor.g = g;
    m_textColor.b = b;
    m_textColor.a = a;
}

void UITextBox::SetBackgroundColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
    m_bgColor.r = r;
    m_bgColor.g = g;
    m_bgColor.b = b;
    m_bgColor.a = a;
}

void UITextBox::Draw()
{
    // Text Rect
    SDL_SetRenderDrawColor( Application::GetRenderer(), m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a );
    SDL_RenderFillRect( Application::GetRenderer(), &m_position );
    // Outline
    SDL_SetRenderDrawColor( Application::GetRenderer(), 0, 0, 0, 255 );
    SDL_RenderDrawRect( Application::GetRenderer(), &m_position );
    // Text
    kuko::ImageManager::Draw( m_sprite );
}

void UITextBox::Update()
{
}

void UITextBox::GenerateTexture()
{
    Logger::Out( "text: " + m_label );
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( m_font, m_label.c_str(), m_textColor );
    m_sprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), textSurface ) );
    SDL_FreeSurface( textSurface );

    m_sprite.position = m_position;

    // Set w/h to fit the ratio
    int fullWidth, fullHeight;
    SDL_QueryTexture( m_sprite.texture, NULL, NULL, &fullWidth, &fullHeight );

    float fontRatio = float(fullWidth) / float(fullHeight);

    m_sprite.position.w = m_sprite.position.h * fontRatio;
    m_sprite.position.x += 2;
}

}
