// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_MAPMANAGER
#define _KUKO_MAPMANAGER

#include <string>

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

    protected:
    static std::string m_currentMap;
};

}

#endif

