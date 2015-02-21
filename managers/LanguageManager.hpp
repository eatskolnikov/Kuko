// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LANGUAGEMANAGER
#define _KUKO_LANGUAGEMANAGER

#include <SDL.h>
#include <SDL_ttf.h>

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

    static std::string Text( const std::string& key );

    protected:
};

}

#endif
