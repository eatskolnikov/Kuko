// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#ifndef _KUKO_MAP
#define _KUKO_MAP

#include <vector>
#include <string>

#include "BaseEntity.hpp"

namespace kuko
{

class Map
{
    public:
//    ~Map();
    void Setup( const std::string& id, const std::string& file, SDL_Texture* tileset, int widthHeight );
    void Draw();

    int GetWidth();
    int GetHeight();

    private:
    std::vector<BaseEntity> m_lstTiles;
    kuko::PositionRect m_offset;
    int m_tileWH;
};

}

#endif
