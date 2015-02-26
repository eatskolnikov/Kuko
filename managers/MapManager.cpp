#include "MapManager.hpp"
#include "LuaManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::string MapManager::m_currentMap;
std::map<int, bool> MapManager::m_solidTiles;

void MapManager::LoadMap( const std::string& id, const std::string& path )
{
    LuaManager::LoadScript( path );
    // Load in the solid tiles
    LoadSolidTileTypes();
}

int MapManager::GetMapWidth()
{
    return LuaManager::Map_GetWidth();
}

int MapManager::GetMapHeight()
{
    return LuaManager::Map_GetHeight();
}

int MapManager::GetTileWidth()
{
    return LuaManager::Map_GetTileWidth();
}

int MapManager::GetTilesetWidth()
{
    return LuaManager::Map_GetTilesetWidth();
}

int MapManager::GetTileFrame( int index )
{
    return LuaManager::Map_GetTileType( index );
}

bool MapManager::GetTileSolidity( int frameIndex )
{
    return ( m_solidTiles[ frameIndex ] == true ) ? true : false;
}

void MapManager::LoadSolidTileTypes()
{
    //m_solidTiles.clear();
    int customTileCount = LuaManager::Map_GetCustomPropertyCount();

    for ( int i = 0; i < customTileCount; i++ )
    {
        int index = LuaManager::Map_GetTileIndex( i );
        bool isSolid = LuaManager::Map_GetTileSolidity( i );
        m_solidTiles.insert( std::pair< int, bool >( index, isSolid ) );
    }
}

}
