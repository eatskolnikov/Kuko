#include "Map.hpp"

#include "../base/Sprite.hpp"
#include "../base/Application.hpp"
#include "../managers/LuaManager.hpp"

namespace kuko
{

void Map::Setup( const std::string& id, const std::string& file, SDL_Texture* tileset, int widthHeight )
{
    Logger::Out( "Loading map \"" + file + "\"", "Map::Setup" );

    LuaManager::LoadScript( file );

    int mapWidth = LuaManager::Map_GetWidth();
    int mapHeight = LuaManager::Map_GetHeight();

    m_tileWH = LuaManager::Map_GetTileWidth();
    int tilesetWidth = LuaManager::Map_GetTilesetWidth();

    m_offset.w = mapWidth * m_tileWH;
    m_offset.h = mapHeight * m_tileWH;

    // Load in the tiles
    // Currently assumes square tiles

    for ( int i = 0; i < ( mapWidth * mapHeight ); i++ )
    {
        int frame = LuaManager::Map_GetTileType( i );
        int frameX = ( frame % tilesetWidth ) * m_tileWH;
        int frameY = ( frame / tilesetWidth ) * m_tileWH;

        int x = int( i % int ( mapWidth ) );
        int y = int( i / int ( mapHeight ) );

        BaseEntity tile;
        tile.Setup( "t-" + I2S( i ), tileset, { x * m_tileWH, y * m_tileWH, m_tileWH, m_tileWH } );
        tile.SetFrame( { frameX, frameY, m_tileWH, m_tileWH } );
        m_lstTiles.push_back( tile );
    }
}

int Map::GetWidth()
{
    return m_offset.w;
}

int Map::GetHeight()
{
    return m_offset.h;
}

void Map::Draw()
{
    for ( unsigned int i = 0; i < m_lstTiles.size(); i++ )
    {
        m_lstTiles[i].Draw();
    }
}

}
