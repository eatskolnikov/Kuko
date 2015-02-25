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

void Map::Setup( const std::string& id, SDL_Texture* tileset, int widthHeight )
{
    Logger::Out( "Map Setup, map width/height is " + I2S( widthHeight ), "Map::Setup" );
    int tileWH = 40;
    m_tileWH = tileWH;
    m_offset.x = m_offset.y = 0;
    m_offset.w = m_offset.h = widthHeight;

    for ( int y = 0; y < widthHeight / tileWH; y++ )
    {
        for ( int x = 0; x < widthHeight / tileWH; x++ )
        {
            BaseEntity tile;
            tile.Setup( "t", tileset, { x * tileWH, y * tileWH, tileWH, tileWH } );
            m_lstTiles.push_back( tile );
        }
    }
    Logger::Out( "Tile width/height is " + I2S( m_tileWH ), "Map::Setup" );
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
