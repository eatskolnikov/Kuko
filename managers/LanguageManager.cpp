// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "LanguageManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::map<std::string, std::string> LanguageManager::m_text;

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
}

void LanguageManager::ClearLanguages()
{
}

const std::string& LanguageManager::Text( const std::string& key )
{
}

void LanguageManager::LoadFile( const std::string& path )
{
}

}
