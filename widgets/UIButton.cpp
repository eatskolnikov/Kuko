#include "UIButton.hpp"

namespace kuko
{

void UIButton::Setup( const std::string& id, const std::string& text, int posX, int posY, int width, int height,
    SDL_Texture* ptrTexture, SDL_Color textColor, TTF_Font* font )
{
    Logger::Out( "Creating UIButton \"" + id + "\"", "UIButton::Setup" );

    m_position.x = posX;
    m_position.y = posY;
    m_position.w = width;
    m_position.h = height;

    m_id = id;

    m_background.Setup( id + "-img", posX, posY, width, height, ptrTexture );
    m_background.SetColor( 0xFF, 0x00, 0x00, 0xFF );\

    m_text.Setup( id + "-lbl", text, font, posX, posY, width, height, textColor );
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
