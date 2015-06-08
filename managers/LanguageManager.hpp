// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LANGUAGEMANAGER
#define _KUKO_LANGUAGEMANAGER

#include <SDL.h>

#include <string>

#include "interfaces/ILanguage.hpp"

namespace kuko
{

class LanguageManager
{
    public:
    // Setup
    static void Setup();
    static void Cleanup();

    static void AddLanguage( const std::string& id, const std::string& path );

    static std::string Text( const std::string& key );
    static std::string Text( const std::string& langType, const std::string& key );
    static std::string CurrentLanguage();

    static std::string GetSuggestedFont();

    static std::string SpecialField( const std::string& langType, const std::string& field, const std::string& key );
    static std::string SpecialField( const std::string& langType, const std::string& field, int key );
    static int SpecialFieldCount( const std::string& langType, const std::string& field );

    protected:
    static ILanguage* m_language;
};

}

#endif
