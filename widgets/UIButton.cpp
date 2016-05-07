#include "UIButton.hpp"

#include "../base/Application.hpp"
#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

UIButton::UIButton() : IWidget()
{
    m_useText = false;
    HandlerFunction = NULL;
}

UIButton::~UIButton()
{
}

void UIButton::Setup( const std::string& id, FloatRect position, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor )
{
    if ( centered )
    {
        position.x = kuko::Application::GetDefaultWidth() / 2 - position.w / 2;
        Logger::Out( "Screen width: " + StringUtil::IntToString( kuko::Application::GetScreenWidth() ) );
    }

    m_position = position;
    m_id = id;
    m_background[0].Setup( id + "-img", position, ptrTexture );
    m_background[0].SetColor( buttonColor );
}

void UIButton::SetTexture( SDL_Texture* ptrTexture )
{
    m_background[0].SetTexture( ptrTexture );
}

void UIButton::Setup( const std::string& id, const std::string& text, FloatRect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, int padding /* = 0 */ )
{
    Setup( id, text, position, centered, ptrTexture, buttonColor, textColor, font, IntRect( padding, padding, padding, padding ) );
}

void UIButton::SetupAnimateEffect( const std::string& effectType, SDL_Texture* frame2, int effectMax )
{
    m_effectMax = effectMax;
    m_effect = effectType;
    m_background[1].Setup( m_id + "-alt-img", m_position, frame2 );
}

void UIButton::SetFrame( IntRect fr )
{
    m_background[0].SetFrame( fr );
    m_background[1].SetFrame( fr );
}

IntRect UIButton::GetFrame()
{
    return m_background[0].GetFrame();
}

void UIButton::Setup( const std::string& id, const std::string& text, FloatRect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, IntRect padding )
{
    FloatRect textPos( position.x + padding.x, position.y + padding.y, position.w - ( padding.w * 2 ), position.h - ( padding.h * 2 ) );
    m_text.Setup( id + "-lbl", text, textPos, centered, textColor, font );
    m_useText = true;
    Setup( id, position, centered, ptrTexture, buttonColor );
}

void UIButton::SetPosition( const IntRect& pos )
{
    IWidget::SetPosition( pos );
    m_background[0].SetPosition( pos );
    m_background[1].SetPosition( pos );
    m_text.SetPosition( pos );
}

void UIButton::SetPosition( float x, float y, float w, float h )
{
    IWidget::SetPosition( x, y, w, h );
    m_background[0].SetPosition( x, y, w, h );
    m_background[1].SetPosition( x, y, w, h );
    m_text.SetPosition( x, y, w, h );
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

UILabel& UIButton::GetLabel()
{
    return m_text;
}

void UIButton::SetTextPosition( const kuko::FloatRect& pos )
{
    m_text.SetPosition( pos );
}

}
