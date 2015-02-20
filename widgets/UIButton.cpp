#include "UIButton.hpp"

namespace kuko
{

void UIButton::Setup( const std::string& id, const std::string& text, SDL_Rect position,
    SDL_Texture* ptrTexture, SDL_Color textColor, TTF_Font* font, int padding /* = 0 */ )
{
    Logger::Out( "Creating UIButton \"" + id + "\"", "UIButton::Setup" );

    m_position = position;

    m_id = id;

    m_background.Setup( id + "-img", position, ptrTexture );
    m_background.SetColor( 0xFF, 0x00, 0x00, 0xFF );

    SDL_Rect textPos = position;
    textPos.x += padding;
    textPos.y += padding;
    textPos.w -= (padding * 2);
    textPos.h -= (padding * 2);

    m_text.Setup( id + "-lbl", text, font, textPos, textColor );
}

void UIButton::Draw()
{
    m_background.Draw();
    m_text.Draw();
}

bool UIButton::IsTriggered( int actionX, int actionY )
{
    return (    actionX >= m_position.x &&
                actionX <= m_position.x + m_position.w &&
                actionY >= m_position.y &&
                actionY <= m_position.y + m_position.h );
}

}
