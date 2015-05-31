// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "LanguageManager.hpp"
#include "LuaManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::string LanguageManager::m_currentLanguage;

void LanguageManager::AddLanguage( const std::string& id, const std::string& path )
{
    m_currentLanguage = id;
    kuko::LuaManager::LoadScript( path );
}

std::string LanguageManager::CurrentLanguage()
{
    return m_currentLanguage;
}

std::string LanguageManager::Text( const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetText( key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LanguageManager::Text( const std::string& langType, const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetText( langType, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LanguageManager::GetSuggestedFont()
{
    std::string suggested = kuko::LuaManager::Language_GetSuggestedFont();
    Logger::Out( "Suggested font: " + suggested );
    return suggested;
}

std::string LanguageManager::SpecialField( const std::string& langType, const std::string& field, const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LanguageManager::SpecialField( const std::string& langType, const std::string& field, int key )
{
    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

int LanguageManager::SpecialFieldCount( const std::string& langType, const std::string& field )
{
    int value = kuko::LuaManager::Language_GetSpecialFieldCount( langType, field );
    return value;
}

}
