// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "BaseEntity.hpp"

#include "../managers/ImageManager.hpp"

namespace kuko
{

void BaseEntity::Setup( const std::string& name, SDL_Texture* texture, PositionRect pos )
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

void BaseEntity::SetFrame( SDL_Rect frame )
{
    m_sprite.frame = frame;
    UpdateSprite();
}

void BaseEntity::SetPosition( int x, int y )
{
    Logger::Out( I2S( x ) + "," + I2S( y ) );
    m_position.x = x;
    m_position.y = y;
    UpdateSprite();
}

PositionRect BaseEntity::GetPosition() const
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
    PositionRect otherRect = other.GetPosition();
    bool col = (
                m_position.x < otherRect.x + otherRect.w &&
                m_position.x + m_position.w > otherRect.x &&
                m_position.y < otherRect.y + otherRect.h &&
                m_position.y + m_position.h > otherRect.y );
    return col;
}

}

