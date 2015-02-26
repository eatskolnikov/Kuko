#include "MapManager.hpp"
#include "LuaManager.hpp"

namespace kuko
{

std::string MapManager::m_currentMap;

void MapManager::LoadMap( const std::string& id, const std::string& path )
{
    LuaManager::LoadScript( path );
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

}
