#include "ConfigManager.hpp"

#include <fstream>

#include "LanguageManager.hpp"
#include "FontManager.hpp"

#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{

std::map<std::string, std::string> ConfigManager::m_settings;
std::map<std::string, std::string> ConfigManager::m_saveData;

bool ConfigManager::LoadConfig()
{
    if ( !LuaManager::LoadScript( "config.lua" ) )
    {
        CreateNewConfig();
        return false;
    }

    // Load in values to the key/value
    SetOption( "helper", LuaManager::Config_GetOption( "helper" ) );

    return true;
}

void ConfigManager::SetOption( const std::string& key, const std::string& val )
{
    Logger::Out( "Set config option \"" + key + "\" to value \"" + val + "\".", "ConfigManager::SetOption" );
    m_settings[ key ] = val;
    SaveConfig();
}

std::string ConfigManager::GetOption( const std::string& key )
{
    return m_settings[ key ];
}

/*
    I need to do research on whether the
    standard lua lib has functionality for writing out lua.
*/

void ConfigManager::SaveConfig()
{
    Logger::Out( "Write out config file", "ConfigManager::SaveConfig" );

    std::ofstream out;
    out.open( "config.lua" );

    out << "config = {" << std::endl;

    for ( std::map<std::string, std::string>::iterator it = m_settings.begin();
        it != m_settings.end(); ++it )
    {
        out << "\t" << it->first << " = \"" << it->second << "\"," << std::endl;
    }

    out << "}" << std::endl;

    out.close();
}

void ConfigManager::CreateNewConfig()
{
    Logger::Out( "Creating new config file", "ConfigManager::CreateNewConfig" );

    SetOption( "savegame_count", "0" );
}

void ConfigManager::CreateNewSave( const std::string& filename )
{
    int savegameCount = StringUtil::StringToInt( GetOption( "savegame_count" ) );
}

void ConfigManager::SaveState()
{
}

void ConfigManager::LoadState( const std::string& filename )
{
}

std::string ConfigManager::GetSaveData( const std::string& key )
{
}

}
