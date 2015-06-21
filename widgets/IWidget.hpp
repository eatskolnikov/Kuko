// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_IWIDGET
#define _KUKO_IWIDGET

#include <SDL.h>

#include "../base/PositionRect.hpp"

#include <string>

namespace kuko
{

class IWidget
{
    public:
    IWidget() { m_visiblePage = 0; /* all pages by default */ }
    virtual void Draw() = 0;
    virtual void Update()
    {
        m_effectTimer--;
        if ( m_effectTimer < 0 ) { m_effectTimer = m_effectMax; }
    }

    PositionRect GetPosition()
    {
        return m_position;
    }

    void SetPosition( float x, float y, float w, float h )
    {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;
    }

    void SetPosition( SDL_Rect pos )
    {
        m_position.Set( pos );
    }

    void SetPosition( PositionRect pos )
    {
        m_position = pos;
    }

    std::string GetId() { return m_id; }
    void SetEffect( const std::string& effect, int effectMax ) { m_effect = effect; m_effectMax = effectMax; m_effectTimer = 0; }

    int GetVisiblePage() { return m_visiblePage; }
    void SetVisiblePage( int val ) { m_visiblePage = val; }

    protected:
    std::string m_id;
    PositionRect m_position;
    int m_visiblePage;

    std::string m_effect;
    int m_effectTimer;
    int m_effectMax;
};

}

#endif
