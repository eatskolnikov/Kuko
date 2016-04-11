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

IntRect BaseEntity::GetFrame()
{
    return m_sprite.GetFrame();
}

void BaseEntity::Update()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Draw()
{
    ImageManager::Draw( m_sprite );

    if ( m_debugFrame )
    {
        kuko::ImageManager::DrawRectangle( m_position, 0, 0, 255 );
    }
}

void BaseEntity::DrawWithOffset( float offsetX, float offsetY )
{
    ImageManager::DrawWithOffset( m_sprite, offsetX, offsetY );
}

bool BaseEntity::IsCollision( const BaseEntity& other )
{
    return IsCollision( other.GetPosition() );
}


bool BaseEntity::IsCollision( const FloatRect& otherRect )
{

    bool col = ( m_isSolid &&
                m_position.x < otherRect.x + otherRect.w &&
                m_position.x + m_position.w > otherRect.x &&
                m_position.y < otherRect.y + otherRect.h &&
                m_position.y + m_position.h > otherRect.y );
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

