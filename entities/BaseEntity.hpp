// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_BASEENTITY
#define _KUKO_BASEENTITY

#include <SDL.h>

#include "../base/Sprite.hpp"

namespace kuko
{

class BaseEntity
{
    public:
    virtual void Setup();
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();

    protected:
    std::string m_id;
    SDL_Rect m_position;
    Sprite m_sprite;

    void UpdateSprite();
};

}

#endif

