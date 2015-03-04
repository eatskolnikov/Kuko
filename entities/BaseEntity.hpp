// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_BASEENTITY
#define _KUKO_BASEENTITY

#include <SDL.h>

#include "../base/Sprite.hpp"
#include "../base/PositionRect.hpp"
#include "../managers/LuaManager.hpp"

namespace kuko
{

class BaseEntity
{
    public:
    BaseEntity( LuaManager* ptrLuaManager, int index );
    virtual void Setup( int index );
    virtual void SetFrame( SDL_Rect frame );
    virtual void Cleanup();

    virtual void Update();
    virtual Sprite& GetSprite();

    virtual kuko::PositionRect GetPosition() const;
    void SetPosition( int x, int y );

    bool IsCollision( const BaseEntity& other );
    bool IsCollision( const PositionRect& otherRect );
    bool IsSolid();
    void SetSolid( bool val );

    protected:
    LuaManager* m_ptrLuaMgr;
    std::string m_id;
    kuko::PositionRect m_position;
    Sprite m_sprite;
    bool m_isSolid;

    void UpdatePosition();
    void UpdateSprite();
};

}

#endif

