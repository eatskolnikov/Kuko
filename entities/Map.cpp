#include "Map.hpp"

#include "../base/Sprite.hpp"
#include "../base/Application.hpp"

namespace kuko
{

//Map::~Map()
//{
//    for ( unsigned int i = 0; i < m_lstTiles.size(); i++ )
//    {
//        if ( m_lstTiles[i] != NULL )
//        {
//            delete m_lstTiles[i];
//            m_lstTiles[i] = NULL;
//        }
//    }
//}

void Map::Setup( const std::string& id, SDL_Texture* tileset )
{
    int tileWH = 40;
    for ( int y = 0; y < kuko::Application::GetScreenHeight() / tileWH; y++ )
    {
        for ( int x = 0; x < kuko::Application::GetScreenWidth() / tileWH; x++ )
        {
            BaseEntity tile;
            tile.Setup( "t", tileset, { x * tileWH, y * tileWH, tileWH, tileWH } );
            m_lstTiles.push_back( tile );
        }
    }
}

void Map::Draw()
{
    for ( unsigned int i = 0; i < m_lstTiles.size(); i++ )
    {
        m_lstTiles[i].Draw();
    }
}

}
