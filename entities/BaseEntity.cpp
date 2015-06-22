// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "BaseEntity.hpp"

#include "../managers/ImageManager.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

void BaseEntity::Setup( const std::string& name, SDL_Texture* texture, FloatRect pos )
{
    m_id = name;
    m_sprite.SetTexture( texture );
    m_position = pos;
    UpdateSprite();
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

void BaseEntity::SetPosition( int x, int y )
{
    Logger::Out( StringUtil::IntToString( x ) + "," + StringUtil::IntToString( y ) );
    m_position.x = x;
    m_position.y = y;
    UpdateSprite();
}

FloatRect BaseEntity::GetPosition() const
{
    return m_position;
}

void BaseEntity::Update()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Draw()
{
    ImageManager::Draw( m_sprite );
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

}

