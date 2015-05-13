#include "ConfigManager.hpp"

#include <fstream>

#include "LanguageManager.hpp"
#include "FontManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

std::map<std::string, std::string> ConfigManager::m_settings;

bool ConfigManager::LoadConfig()
{
    if ( !LuaManager::LoadScript( "config.lua" ) )
    {
        CreateNewConfig();
        return false;
    }

    // Load in values to the key/value
    SetConfig( "helper", LuaManager::Config_GetOption( "helper" ) );
    Logger::Out( "Helper is " + m_settings[ "helper" ], "", true, 1 );
    kuko::LanguageManager::AddLanguage( "helper", "languages/" + m_settings[ "helper" ] + "_helper.lua" );
    // Load appropriate font
    if ( m_settings[ "helper" ] == "english" || m_settings[ "helper" ] == "esperanto" || m_settings[ "helper" ] == "piglatin" )
    {
        kuko::FontManager::ReplaceFont( "helper", "font/NotoSans-Bold.ttf", 28 );
    }

    return true;
}

void ConfigManager::SetConfig( const std::string& key, const std::string& val )
{
    m_settings[ key ] = val;
    SaveConfig();
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

    std::ofstream out;
    out.open( "config.lua" );

    out << "config = {" << std::endl;
    out << "}" << std::endl;

    out.close();
}

}
