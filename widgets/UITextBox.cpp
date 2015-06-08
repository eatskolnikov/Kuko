#include "UITextBox.hpp"

#include "../base/Application.hpp"
#include "../managers/ImageManager.hpp"

namespace kuko
{

UITextBox::UITextBox()
{
    m_label = "";
}

void UITextBox::Setup( const std::string& id, SDL_Rect position, SDL_Color bgColor, SDL_Color selectedColor, SDL_Color textColor, TTF_Font* font, int maxChars )
{
    Logger::Out( "Setup " + id, "UITextBox::Setup" );
    m_id = id;
    m_position.Set( position );
    m_textColor = textColor;
    m_bgColor = bgColor;
    m_defaultBgColor = bgColor;
    m_selectedBgColor = selectedColor;
    m_font = font;
    GenerateTexture();
    SDL_SetTextInputRect( &position );
    m_maxChars = maxChars;
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
    SDL_Rect rect = m_position.ToSDLRect();
    // Text Rect
    SDL_SetRenderDrawColor( Application::GetRenderer(), m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a );
    SDL_RenderFillRect( Application::GetRenderer(), &rect );
    // Outline
    SDL_SetRenderDrawColor( Application::GetRenderer(), 0, 0, 0, 255 );
    SDL_RenderDrawRect( Application::GetRenderer(), &rect );
    // Text
    kuko::ImageManager::Draw( m_sprite );
}

void UITextBox::SetActive( bool val )
{
    if ( val )
    {
        m_bgColor = m_selectedBgColor;
    }
    else
    {
        m_bgColor = m_defaultBgColor;
    }
}

void UITextBox::Update()
{
}


void UITextBox::SetText( const std::string& text )
{
    m_label = text;
    GenerateTexture();
}

std::string UITextBox::GetText()
{
    return m_label;
}

void UITextBox::AppendText( const std::string& text )
{
    m_label += text;
    GenerateTexture();
}

void UITextBox::RemoveLastLetter()
{
    m_label = m_label.substr( 0, m_label.size() - 1 );
    GenerateTexture();
}

void UITextBox::ValidateText()
{
    if ( m_label.size() > m_maxChars )
    {
        m_label = m_label.substr( 0, m_maxChars );
    }
}

void UITextBox::GenerateTexture()
{
    ValidateText();

    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( m_font, m_label.c_str(), m_textColor );
    m_sprite.SetTexture ( SDL_CreateTextureFromSurface( kuko::Application::GetRenderer(), textSurface ) );
    SDL_FreeSurface( textSurface );

    m_sprite.position = m_position.ToSDLRect();

    // Set w/h to fit the ratio
    int fullWidth, fullHeight;
    SDL_QueryTexture( m_sprite.texture, NULL, NULL, &fullWidth, &fullHeight );

    float fontRatio = float(fullWidth) / float(fullHeight);

    m_sprite.position.w = m_sprite.position.h * fontRatio;
    m_sprite.position.x += 2;
}

}
