// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_FONTANAGER
#define _KUKO_FONTANAGER

#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include <string>

namespace kuko
{

class FontManager
{
    public:
    static void Setup();
    static void Cleanup();

    static void AddFont( const std::string& id, const std::string& path, int size );
    static void ClearFonts();
    static TTF_Font* GetFont( const std::string& key );

    protected:
    static std::map<std::string, TTF_Font*> m_fonts;
    static TTF_Font* LoadFile( const std::string& path );
};

}

#endif
