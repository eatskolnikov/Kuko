// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_FONTMANAGER
#define _KUKO_FONTMANAGER

#include <SDL.h>
#include "SDL_ttf.h"

#include <map>
#include <string>

namespace kuko
{

class FontManager
{
    public:
    void Setup();
    void Cleanup();

    void AddFont( const std::string& id, const std::string& path, int size );
    void ClearFonts();
    TTF_Font* GetFont( const std::string& key );

    protected:
    std::map<std::string, TTF_Font*> m_fonts;
    TTF_Font* LoadFile( const std::string& path );
};

}

#endif
