// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "BaseEntity.hpp"

#include "../managers/ImageManager.hpp"

namespace kuko
{

void BaseEntity::Setup( const std::string& name, SDL_Texture* texture )
{
    m_id = name;
    m_sprite.SetTexture( texture );
}

void BaseEntity::UpdateSprite()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Cleanup()
{
}

PositionRect BaseEntity::GetPosition()
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

}

