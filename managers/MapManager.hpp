// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_MAPMANAGER
#define _KUKO_MAPMANAGER

#include <string>
#include <map>

namespace kuko
{

class MapManager
{
    public:
    void LoadMap( const std::string& id, const std::string& path );

    int GetMapWidth();
    int GetMapHeight();

    int GetTileWidth();
    int GetTilesetWidth();

    int GetTileFrame( int index );
    bool GetTileSolidity( int frameIndex );

    protected:
    std::string m_currentMap;
    std::map<int, bool> m_solidTiles;

    void LoadSolidTileTypes();
};

}

#endif

