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
    void Setup( const std::string& id, SDL_Texture* tileset );
    void Draw();

    private:
    std::vector<BaseEntity> m_lstTiles;
};

}

#endif
