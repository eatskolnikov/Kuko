// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "BaseEntity.hpp"

#include "../managers/ImageManager.hpp"

namespace kuko
{

BaseEntity::BaseEntity( LuaManager* ptrLuaManager, ImageManager* ptrImageManager, int index )
{
    Logger::Out( "begin", "BaseEntity::BaseEntity" );

    m_ptrImgMgr = ptrImageManager;

    m_ptrLuaMgr = ptrLuaManager;
    Setup( index );

    Logger::Out( "end", "BaseEntity::BaseEntity" );
}

void BaseEntity::Setup( int index )
{
    m_id = m_ptrLuaMgr->State_GetEntityName( index );
    Logger::Out( "New Entity Name: " + m_id );

    // Set position
    UpdatePosition();

    // Set texture
    std::string texturePath = m_ptrLuaMgr->State_GetEntityTextureFile( m_id );
    Logger::Out( "Texture path " + texturePath );
    m_ptrImgMgr->AddTexture( m_id, texturePath );
    m_sprite.SetTexture( m_ptrImgMgr->GetTexture( m_id ) );

    UpdateSprite();
}

void BaseEntity::UpdatePosition()
{
    std::vector<int> posResults = m_ptrLuaMgr->State_GetEntityPosition( m_id );
    // values are popped off the stack in opposite order?
    m_position.x = posResults[3];
    m_position.y = posResults[2];
    m_position.w = posResults[1];
    m_position.h = posResults[0];
}

void BaseEntity::UpdateSprite()
{
    m_sprite.SetPosition( m_position );
}

void BaseEntity::SetFrame()
{
    int fr = m_ptrLuaMgr->State_GetEntityFrame( m_id ) * m_position.w;
    m_sprite.frame = { fr, 0, m_position.w, m_position.h };
    UpdateSprite();
}

PositionRect BaseEntity::GetPosition() const
{
    return m_position;
}

void BaseEntity::Update()
{
    UpdatePosition();
    SetFrame();
    m_sprite.SetPosition( m_position );
}

void BaseEntity::Draw()
{
    m_ptrImgMgr->Draw( m_sprite );
}

}

