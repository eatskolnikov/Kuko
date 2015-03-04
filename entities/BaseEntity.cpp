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
    Logger::Out( "begin", "BaseEntity::UpdatePosition" );

    std::vector<int> posResults = m_ptrLuaMgr->State_GetEntityPosition( m_id );
    m_position.x = posResults[0];
    m_position.y = posResults[1];
    m_position.w = posResults[2];
    m_position.h = posResults[3];

    Logger::Out( "Pos: " + I2S( m_position.x ) + "," + I2S( m_position.y ) + " - "
        + I2S( m_position.w ) + "x" + I2S( m_position.h ) );
}

void BaseEntity::UpdateSprite()
{
    m_sprite.SetPosition( m_position );
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
    m_ptrImgMgr->Draw( m_sprite );
}

bool BaseEntity::IsCollision( const BaseEntity& other )
{
    return IsCollision( other.GetPosition() );
}


bool BaseEntity::IsCollision( const PositionRect& otherRect )
{

    bool col = ( m_isSolid &&
                m_position.x < otherRect.x + otherRect.w &&
                m_position.x + m_position.w > otherRect.x &&
                m_position.y < otherRect.y + otherRect.h &&
                m_position.y + m_position.h > otherRect.y );
    return col;
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

