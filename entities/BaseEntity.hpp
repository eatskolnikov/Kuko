// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_BASEENTITY
#define _KUKO_BASEENTITY

#include <SDL.h>

#include "../base/Sprite.hpp"
#include "../base/PositionRect.hpp"
#include "../managers/LuaManager.hpp"
#include "../managers/ImageManager.hpp"

namespace kuko
{

class BaseEntity
{
    public:
    BaseEntity( LuaManager* ptrLuaManager, ImageManager* ptrImageManager, int index );
    virtual void Setup( int index );
    virtual void SetFrame( SDL_Rect frame );

    virtual void Update();
    virtual void Draw();

    virtual kuko::PositionRect GetPosition() const;
    void SetPosition( int x, int y );

    bool IsCollision( const BaseEntity& other );
    bool IsCollision( const PositionRect& otherRect );
    bool IsSolid();
    void SetSolid( bool val );

    protected:
    LuaManager* m_ptrLuaMgr;
    ImageManager* m_ptrImgMgr; // TODO: I don't really like this.

    std::string m_id;
    kuko::PositionRect m_position;
    Sprite m_sprite;
    bool m_isSolid;

    void UpdatePosition();
    void UpdateSprite();
};

}

#endif

