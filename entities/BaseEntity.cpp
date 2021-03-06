// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "BaseEntity.hpp"

#include "../managers/ImageManager.hpp"
#include "../utilities/StringUtil.hpp"
#include "../base/Application.hpp"

namespace kuko
{

void BaseEntity::Setup( const std::string& name, SDL_Texture* texture, FloatRect pos )
{
    m_id = name;
    m_sprite.SetTexture( texture );
    m_position = pos;
    m_collisionRegion = kuko::FloatRect( 0, 0, pos.w, pos.h );
    UpdateSprite();
}

void BaseEntity::SetTexture( SDL_Texture* texture )
{
    m_sprite.SetTexture( texture );
}

void BaseEntity::UpdateSprite()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Cleanup()
{
}

void BaseEntity::SetFrame( IntRect frame )
{
    m_sprite.frame = frame;
    UpdateSprite();
}

void BaseEntity::SetPosition( float x, float y )
{
    m_position.x = x;
    m_position.y = y;
    UpdateSprite();
}

void BaseEntity::SetPosition( const FloatRect& pos )
{
    m_position = pos;
    UpdateSprite();
}

FloatRect BaseEntity::GetPosition() const
{
    return m_position;
}

void BaseEntity::SetCollisionRegion( const FloatRect& pos )
{
    m_collisionRegion = pos;
}

kuko::FloatRect BaseEntity::GetCollisionRegion()
{
    return m_collisionRegion;
}

kuko::FloatRect BaseEntity::GetCollisionRegionAtPosition() const
{
    kuko::FloatRect collision = m_collisionRegion;
    collision.x += m_position.x;
    collision.y += m_position.y;
    return collision;
}

IntRect BaseEntity::GetFrame()
{
    return m_sprite.GetFrame();
}

void BaseEntity::SetRotation( float angle )
{
    m_sprite.SetRotation( angle );
}

float BaseEntity::GetRotation()
{
    return m_sprite.GetRotation();
}

void BaseEntity::Update()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Draw()
{
    m_sprite.Draw();
}

bool BaseEntity::IsCollision( const BaseEntity& other )
{
    kuko::FloatRect rect = other.GetCollisionRegionAtPosition();
    return IsCollision( rect );
}


bool BaseEntity::IsCollision( const FloatRect& r2 )
{
    kuko::FloatRect r1 = GetCollisionRegionAtPosition();

    bool col = ( m_isSolid &&
                r1.x < r2.x + r2.w &&
                r1.x + r1.w > r2.x &&
                r1.y < r2.y + r2.h &&
                r1.y + r1.h > r2.y );
    return col;
}

bool BaseEntity::IsClicked( int x, int y )
{
    return (    m_position.x <= x &&
                m_position.x + m_position.w > x &&
                m_position.y <= y &&
                m_position.y + m_position.h > y );
}

bool BaseEntity::IsSolid()
{
    return m_isSolid;
}

void BaseEntity::SetSolid( bool val )
{
    m_isSolid = val;
}

void BaseEntity::SetDebugFrame( bool val )
{
    m_debugFrame = val;
}

}

