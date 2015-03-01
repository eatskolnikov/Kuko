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
    static void AddLanguage( const std::string& id, const std::string& path );

    static std::string Text( const std::string& key );
    static std::string CurrentLanguage();

    static std::string GetSuggestedFont();

    protected:
    static std::string m_currentLanguage;
};

}

#endif
