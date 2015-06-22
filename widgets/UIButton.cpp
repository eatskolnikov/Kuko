#include "UIButton.hpp"

#include "../base/Application.hpp"
#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

UIButton::UIButton() : IWidget()
{
    m_useText = false;
}

void UIButton::Setup( const std::string& id, int x, int y, int w, int h, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor )
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
    Setup( id, pos, centered, ptrTexture, buttonColor );
}

void UIButton::Setup( const std::string& id, SDL_Rect position, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor )
{
    if ( centered )
    {
        position.x = kuko::Application::GetDefaultWidth() / 2 - position.w / 2;
        Logger::Out( "Screen width: " + StringUtil::IntToString( kuko::Application::GetScreenWidth() ) );
    }

    m_position.Set( position );
    m_id = id;
    m_background[0].Setup( id + "-img", position, ptrTexture );
    m_background[0].SetColor( buttonColor );
}

void UIButton::Setup( const std::string& id, const std::string& text, SDL_Rect position, bool centered,
    SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, int padding /* = 0 */ )
{
    Setup( id, text, position, centered, ptrTexture, buttonColor, textColor, font, { padding, padding, padding, padding } );
}

void UIButton::SetupAnimateEffect( const std::string& effectType, SDL_Texture* frame2, int effectMax )
{
    SDL_Rect rect = m_position.ToSDLRect();
    m_effectMax = effectMax;
    m_effect = effectType;
    m_background[1].Setup( m_id + "-alt-img", rect, frame2 );
}

void UIButton::SetFrame( SDL_Rect fr )
{
    m_background[0].SetFrame( fr );
    m_background[1].SetFrame( fr );
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

void UIButton::Update()
{
    m_effectTimer--;
    if ( m_effectTimer < 0 ) { m_effectTimer = m_effectMax; }
}

void UIButton::Draw()
{
    if ( ( m_effect == "" )
        || ( m_effect == "animate" && m_effectTimer < m_effectMax/2 ) )
    {
        m_background[0].Draw();
    }
    else if ( m_effect == "animate" && m_effectTimer >= m_effectMax/2 )
    {
        m_background[1].Draw();
    }

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
