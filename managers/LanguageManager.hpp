// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LANGUAGEMANAGER
#define _KUKO_LANGUAGEMANAGER

#include "LuaManager.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace kuko
{

class LanguageManager
{
    public:
    LanguageManager( LuaManager* ptrLuaManager );

    void AddLanguage( const std::string& id, const std::string& path );

    std::string Text( const std::string& key );
    std::string CurrentLanguage();

    std::string GetSuggestedFont();

    protected:
    std::string m_currentLanguage;
    LuaManager* m_ptrLuaMgr;
};

}

#endif
