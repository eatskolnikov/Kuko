#include "UIButton.hpp"

namespace kuko
{

UIButton::UIButton()
{
    m_useText = false;
}

void UIButton::Setup( const std::string& id, SDL_Rect position, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor )
{
    m_position = position;
    m_id = id;
    m_background.Setup( id + "-img", position, ptrTexture );
    m_background.SetColor( buttonColor );
}

void UIButton::Setup( const std::string& id, const std::string& text, SDL_Rect position, bool centered,
    SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, int padding /* = 0 */ )
{
    Setup( id, text, position, centered, ptrTexture, buttonColor, textColor, font, { padding, padding, padding, padding } );
}

void UIButton::Setup( const std::string& id, const std::string& text, SDL_Rect position, bool centered,
    SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, SDL_Rect padding )
{
    SDL_Rect textPos = position;
    textPos.x += padding.x;
    textPos.y += padding.y;
    textPos.w -= (padding.w * 2);
    textPos.h -= (padding.h * 2);
    m_text.Setup( id + "-lbl", text, textPos, centered, textColor, font );
    m_useText = true;
    Setup( id, position, centered, ptrTexture, buttonColor );
}

void UIButton::Draw()
{
    m_background.Draw();
    if ( m_useText )
    {
        m_text.Draw();
    }
}

bool UIButton::IsTriggered( int actionX, int actionY )
{
    return (    actionX >= m_position.x &&
                actionX <= m_position.x + m_position.w &&
                actionY >= m_position.y &&
                actionY <= m_position.y + m_position.h );
}

}
