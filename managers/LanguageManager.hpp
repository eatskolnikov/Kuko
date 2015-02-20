// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LANGUAGEMANAGER
#define _KUKO_LANGUAGEMANAGER

#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include <string>

namespace kuko
{

class LanguageManager
{
    public:
    static void Setup();
    static void Cleanup();

    static void AddLanguage( const std::string& id, const std::string& path );
    static void ClearLanguages();

    static const std::string& Text( const std::string& key );

    protected:
    static std::map<std::string, std::string> m_text;
    static void LoadFile( const std::string& path );
};

}

#endif
