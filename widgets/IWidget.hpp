// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_IWIDGET
#define _KUKO_IWIDGET

#include <SDL.h>

#include <string>

namespace kuko
{

class IWidget
{
    public:
    IWidget() { m_visiblePage = 0; /* all pages by default */ }
    virtual void Draw() = 0;
    SDL_Rect GetPosition() { return m_position; }
    std::string GetId() { return m_id; }

    int GetVisiblePage() { return m_visiblePage; }
    void SetVisiblePage( int val ) { m_visiblePage = val; }

    protected:
    std::string m_id;
    SDL_Rect m_position;
    int m_visiblePage;
};

}

#endif
