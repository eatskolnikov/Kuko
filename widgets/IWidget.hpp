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
    virtual void Draw() = 0;
    SDL_Rect GetPosition() { return m_position; }
    std::string GetId() { return m_id; }

    protected:
    std::string m_id;
    SDL_Rect m_position;
};

}

#endif
