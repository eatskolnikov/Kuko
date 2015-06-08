#include "ConfigManager.hpp"

#include <fstream>

#include "LanguageManager.hpp"
#include "FontManager.hpp"

#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

#include "LuaConfig.hpp"
#include "LualessConfig.hpp"

namespace kuko
{

bool ConfigManager::m_useLua;
IConfig* ConfigManager::m_config;

void ConfigManager::Setup()
{
    m_config = NULL;
    #ifdef NOLUA
        m_useLua = false;
        m_config = new LualessConfig;
    #else
        m_useLua = true;
        m_config = new LuaConfig;
    #endif
}

void ConfigManager::Cleanup()
{
    if ( m_config != NULL )
    {
        delete m_config;
        m_config = NULL;
    }
}

void ConfigManager::SaveConfig()
{
    m_config->SaveConfig();
}

bool ConfigManager::LoadConfig( const std::vector<std::string>& settings )
{
    return m_config->LoadConfig( settings );
}

void ConfigManager::SetOption( const std::string& key, const std::string& val )
{
    m_config->SetOption( key, val );
}

std::string ConfigManager::GetOption( const std::string& key )
{
    return m_config->GetOption( key );
}

void ConfigManager::CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings )
{
    m_config->CreateNewSave( playername, settings );
}

bool ConfigManager::LoadState( const std::string& filename, const std::vector<std::string>& settings )
{
    return m_config->LoadState( filename, settings );
}

std::string ConfigManager::GetSaveData( const std::string& key )
{
    m_config->GetSaveData( key );
}

void ConfigManager::SetSaveData( const std::string& key, const std::string& val )
{
    m_config->SetSaveData( key, val );
}

void ConfigManager::DeleteCurrentSavefile()
{
    m_config->DeleteCurrentSavefile();
}

std::string ConfigManager::GetSavegameName()
{
    return m_config->GetSavegameName();
}

}
