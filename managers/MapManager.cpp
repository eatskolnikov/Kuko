#include "MapManager.hpp"
#include "LuaManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::string MapManager::m_currentMap;
std::map<int, bool> MapManager::m_solidTiles;

#ifndef NOLUA

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

#else

void MapManager::LoadMap( const std::string& id, const std::string& path )
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::LoadMap" );
}

int MapManager::GetMapWidth()
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetMapWidth" );
    return -1;
}

int MapManager::GetMapHeight()
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetMapHeight" );
    return -1;
}

int MapManager::GetTileWidth()
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetTileWidth" );
    return -1;
}

int MapManager::GetTilesetWidth()
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetTilesetWidth" );
    return -1;
}

int MapManager::GetTileFrame( int index )
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetTileFrame" );
    return -1;
}

bool MapManager::GetTileSolidity( int frameIndex )
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::GetTileSolidity" );
    return -1;
}

void MapManager::LoadSolidTileTypes()
{
    Logger::Error( "Error: Lualess Kuko does not currently support Maps", "MapManager::LoadSolidTileTypes" );
}

#endif

}
