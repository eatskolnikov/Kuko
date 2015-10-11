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
    virtual void Setup( const std::string& name, SDL_Texture* texture, FloatRect pos );
    virtual void SetFrame( IntRect frame );
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();
    virtual void DrawWithOffset( const kuko::FloatRect& camera );

    virtual kuko::FloatRect GetPosition() const;
    void SetPosition( float x, float y );
    void SetPosition( const FloatRect& pos );
    void SetLayer( int val );
    int GetLayer() const;

    bool IsCollision( const BaseEntity& other );
    bool IsCollision( const FloatRect& otherRect );
    bool IsClicked( int x, int y );
    bool IsSolid();
    void SetSolid( bool val );

    protected:
    std::string m_id;
    kuko::FloatRect m_position;
    Sprite m_sprite;
    bool m_isSolid;
    int m_layer;

    void UpdateSprite();
};

}

#endif

