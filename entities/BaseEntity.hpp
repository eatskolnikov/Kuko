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

    virtual kuko::FloatRect GetPosition() const;
    virtual kuko::IntRect GetFrame();
    void SetPosition( float x, float y );
    void SetPosition( const FloatRect& pos );
    void SetCollisionRegion( const FloatRect& pos );
    kuko::FloatRect GetCollisionRegion();
    kuko::FloatRect GetCollisionRegionAtPosition() const;
    virtual void SetTexture( SDL_Texture* texture );
    void SetRotation( float angle );
    float GetRotation();

    bool IsCollision( const BaseEntity& other );
    bool IsCollision( const FloatRect& otherRect );
    bool IsClicked( int x, int y );
    bool IsSolid();
    void SetSolid( bool val );

    void SetDebugFrame( bool val );

    protected:
    std::string m_id;
    kuko::FloatRect m_position;
    kuko::FloatRect m_collisionRegion;
    Sprite m_sprite;
    Sprite m_altSprite;
    bool m_isSolid;
    bool m_debugFrame;

    void UpdateSprite();
};

}

#endif

