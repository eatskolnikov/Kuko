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
std::string ConfigManager::m_currentSavegame;

bool ConfigManager::LoadConfig( const std::vector<std::string>& settings )
{
    if ( !LuaManager::LoadScript( "config.lua" ) )
    {
        CreateNewConfig();
        return false;
    }

    // Load in values to the key/value
    for ( int i = 0; i < settings.size(); i++ )
    {
        SetOption( settings[i], LuaManager::Config_GetOption( settings[i] ) );
    }

    int savegameCount = StringUtil::StringToInt( GetOption( "savegame_count" ) );
    for ( int i = 1; i <= savegameCount; i++ )
    {
        std::string opt = "savegame_" + StringUtil::IntToString( i );
        SetOption( opt, LuaManager::Config_GetOption( opt ) );
    }

    return true;
}

void ConfigManager::SetOption( const std::string& key, const std::string& val )
{
    Logger::Out( "Set config option \"" + key + "\" to value \"" + val + "\".", "ConfigManager::SetOption", "config" );
    m_settings[ key ] = val;
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
    Logger::Out( "Write out config file", "ConfigManager::SaveConfig", "config" );

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
    Logger::Out( "Creating new config file", "ConfigManager::CreateNewConfig", "config" );
    SetOption( "savegame_count", "0" );
    SaveConfig();
}

void ConfigManager::CreateNewSave( const std::string& playername, const std::map<std::string, std::string>& settings )
{
    Logger::Out( "Create a new save file for " + playername, "ConfigManager::CreateNewSave", "config" );
    std::string savegameFile = playername + "-save.lua";
    int savegameCount = StringUtil::StringToInt( GetOption( "savegame_count" ) );
    SetOption( "savegame_" + StringUtil::IntToString(savegameCount + 1), savegameFile );
    m_currentSavegame = savegameFile;

    Logger::Out( "Savegame file is " + m_currentSavegame, "ConfigManager::CreateNewSave", "config" );

    SetSaveData( "name", playername );
    SetSaveData( "helper", GetOption( "helper" ) ); // Get the config file's helper
    SetSaveData( "target", "" );
    SetSaveData( "pronoun", "" );
    SetSaveData( "hair_type", "" );
    SetSaveData( "hair_color", "" );
    SetSaveData( "clothes_type", "" );
    SetSaveData( "face_type", "" );
    SetSaveData( "skin_color", "" );
    SaveState();
}

void ConfigManager::DeleteCurrentSavefile()
{
    remove( m_currentSavegame.c_str() );
    m_currentSavegame = "";
}

void ConfigManager::SaveState()
{
    Logger::Out( "Write out save file \"" + m_currentSavegame + "\"", "ConfigManager::SaveState", "config" );

    std::ofstream out;
    out.open( ("savegames/" + m_currentSavegame).c_str() );

    out << "save = {" << std::endl;

    for ( std::map<std::string, std::string>::iterator it = m_saveData.begin();
        it != m_saveData.end(); ++it )
    {
        out << "\t" << it->first << " = \"" << it->second << "\"," << std::endl;

        Logger::Out( "\t" + it->first + " = " + it->second, "ConfigManager::SaveState", "config" );
    }

    out << "}" << std::endl;

    out.close();
}

bool ConfigManager::LoadState( const std::string& filename )
{
    m_currentSavegame = filename;

    if ( !LuaManager::LoadScript( "savegames/" + m_currentSavegame ) )
    {
        return false;
    }

    // Load in values to the key/value
    SetSaveData( "name", LuaManager::Savegame_GetData( "name" ) );
    SetSaveData( "helper", LuaManager::Savegame_GetData( "helper" ) );
    SetSaveData( "target", LuaManager::Savegame_GetData( "target" ) );
    SetSaveData( "pronoun", LuaManager::Savegame_GetData( "pronoun" ) );
    SetSaveData( "hair_type", LuaManager::Savegame_GetData( "hair_type" ) );
    SetSaveData( "hair_color", LuaManager::Savegame_GetData( "hair_color" ) );
    SetSaveData( "clothes_type", LuaManager::Savegame_GetData( "clothes_type" ) );
    SetSaveData( "face_type", LuaManager::Savegame_GetData( "face_type" ) );
    SetSaveData( "skin_color", LuaManager::Savegame_GetData( "skin_color" ) );

    return true;
}

std::string ConfigManager::GetSaveData( const std::string& key )
{
    return m_saveData[ key ];
}

void ConfigManager::SetSaveData( const std::string& key, const std::string& val )
{
    Logger::Out( "Set save data \"" + key + "\" to value \"" + val + "\".", "ConfigManager::SetSaveData", "config" );
    m_saveData[ key ] = val;
}

std::string ConfigManager::GetSavegameName()
{
    return m_currentSavegame;
}

}
