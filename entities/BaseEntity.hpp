// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_BASEENTITY
#define _KUKO_BASEENTITY

#include <SDL.h>

#include "../base/Sprite.hpp"
#include "../base/PositionRect.hpp"

namespace kuko
{

class BaseEntity
{
    public:
    virtual void Setup( const std::string& name, SDL_Texture* texture, PositionRect pos );
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();

    virtual kuko::PositionRect GetPosition() const;
    void SetPosition( int x, int y );

    bool IsCollision( const BaseEntity& other );

    protected:
    std::string m_id;
    kuko::PositionRect m_position;
    Sprite m_sprite;

    void UpdateSprite();
};

}

#endif
