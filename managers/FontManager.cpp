// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "FontManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

void FontManager::Cleanup()
{
    Logger::Out( "FontManager::Cleanup" );

    for (   std::map<std::string, TTF_Font*>::iterator it = m_fonts.begin();
            it != m_fonts.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            TTF_CloseFont( it->second );
            it->second = NULL;
        }
    }
}

void FontManager::AddFont( const std::string& id, const std::string& path, int size )
{
    Logger::Out( "Add font " + id + " from path " + path, "FontManager::AddFont" );
    m_fonts.insert( std::pair<std::string, TTF_Font*>( id, LoadFile( path ) ) );
}

void FontManager::ClearFonts()
{
    m_fonts.clear();
}

TTF_Font* FontManager::GetFont( const std::string& key )
{
    return m_fonts[ key ];
}

TTF_Font* FontManager::LoadFile( const std::string& path )
{
    Logger::Out( "Load font \"" + path + "\"", "FontManager::LoadFile" );
    TTF_Font* font = TTF_OpenFont( path.c_str(), 28 );
    return font;
}

}
