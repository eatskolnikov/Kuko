// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "LanguageManager.hpp"

#include "interfaces/LuaLanguage.hpp"
#include "../utilities/Logger.hpp"

namespace kuko
{

ILanguage* LanguageManager::m_language;

void LanguageManager::Setup()
{
    m_language = NULL;
    #ifdef NOLUA
        // No config
        Logger::Error( "Language not yet supported without Lua", "LanguageManager::Setup" );
    #else
        Logger::Out( "Setup LuaLanguage", "LanguageManager::Setup" );
        m_language = new LuaLanguage;
    #endif
}

void LanguageManager::Cleanup()
{
    if ( m_language != NULL )
    {
        delete m_language;
        m_language = NULL;
    }
}

void LanguageManager::AddLanguage( const std::string& id, const std::string& path )
{
    Logger::Out( "Add language \"" + id + "\" from path \"" + path + "\"", "LanguageManager::AddLanguage" );
    m_language->AddLanguage( id, path );
}

std::string LanguageManager::CurrentLanguage()
{
    return m_language->CurrentLanguage();
}

std::string LanguageManager::Text( const std::string& key )
{
    return m_language->Text( key );
}

std::string LanguageManager::Text( const std::string& langType, const std::string& key )
{
    std::string value = m_language->Text( langType, key );
    return m_language->Text( langType, key );
}

std::string LanguageManager::GetSuggestedFont()
{
    return m_language->GetSuggestedFont();
}

std::string LanguageManager::SpecialField( const std::string& langType, const std::string& field, const std::string& key )
{
    return m_language->SpecialField( langType, field, key );
}

std::string LanguageManager::SpecialField( const std::string& langType, const std::string& field, int key )
{
    return m_language->SpecialField( langType, field, key );
}

int LanguageManager::SpecialFieldCount( const std::string& langType, const std::string& field )
{
    return m_language->SpecialFieldCount( langType, field );
}

}
