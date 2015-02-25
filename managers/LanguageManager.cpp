// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "LanguageManager.hpp"
#include "LuaManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::string LanguageManager::m_currentLanguage;

void LanguageManager::Setup()
{
    Logger::Out( "LanguageManager::Setup" );
}

void LanguageManager::Cleanup()
{
    Logger::Out( "LanguageManager::Cleanup" );
}

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
    return kuko::LuaManager::Language_GetText( key );
}

}