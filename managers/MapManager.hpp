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
    static void LoadMap( const std::string& id, const std::string& path );

    static int GetMapWidth();
    static int GetMapHeight();

    static int GetTileWidth();
    static int GetTilesetWidth();

    static int GetTileFrame( int index );
    static bool GetTileSolidity( int frameIndex );

    protected:
    static std::string m_currentMap;
    static std::map<int, bool> m_solidTiles;

    static void LoadSolidTileTypes();
};

}

#endif

