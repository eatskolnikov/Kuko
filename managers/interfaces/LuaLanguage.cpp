#include "LuaLanguage.hpp"

#ifndef NOLUA

#include "LuaManager.hpp"

namespace kuko
{

LuaLanguage::LuaLanguage()
{
    Logger::Out( "LuaLanguage Constructor" );
}

bool LuaLanguage::AddLanguage( const std::string& id, const std::string& path )
{
    m_currentLanguage = id;
    return kuko::LuaManager::LoadScript( path );
}

std::string LuaLanguage::CurrentLanguage()
{
    return m_currentLanguage;
}

std::string LuaLanguage::Text( const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetText( key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LuaLanguage::Text( const std::string& langType, const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetText( langType, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LuaLanguage::GetSuggestedFont()
{
    std::string suggested = kuko::LuaManager::Language_GetSuggestedFont();
    Logger::Out( "Suggested font: " + suggested );
    return suggested;
}

std::string LuaLanguage::SpecialField( const std::string& langType, const std::string& field, const std::string& key )
{
    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

std::string LuaLanguage::SpecialField( const std::string& langType, const std::string& field, int key )
{
    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
}

int LuaLanguage::SpecialFieldCount( const std::string& langType, const std::string& field )
{
    int value = kuko::LuaManager::Language_GetSpecialFieldCount( langType, field );
    return value;
}

}

#endif
