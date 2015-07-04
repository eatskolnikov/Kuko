#include "LuaConfig.hpp"

#ifndef NOLUA

#include "../LuaManager.hpp"
#include "../../utilities/StringUtil.hpp"
#include "../../utilities/Logger.hpp"

namespace kuko
{

LuaConfig::LuaConfig()
{
}

bool LuaConfig::LoadConfig( const std::vector<std::string>& settings )
{
    Logger::Out( "Load config file", "LuaConfig::LoadConfig" );
    if ( !LuaManager::LoadScript( "config.lua" ) )
    {
        Logger::Out( "Config file not found, create a new one", "LuaConfig::LoadConfig" );
        CreateNewConfig();
        return false;
    }

    // Load in values to the key/value
    for ( unsigned int i = 0; i < settings.size(); i++ )
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

void LuaConfig::SetOption( const std::string& key, const std::string& val )
{
    Logger::Out( "Set config option \"" + key + "\" to value \"" + val + "\".", "LuaConfig::SetOption", "config" );
    m_settings[ key ] = val;
}

std::string LuaConfig::GetOption( const std::string& key )
{
    return m_settings[ key ];
}

/*
    I need to do research on whether the
    standard lua lib has functionality for writing out lua.
*/

void LuaConfig::SaveConfig()
{
    Logger::Out( "Write out config file", "LuaConfig::SaveConfig", "config" );

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

void LuaConfig::CreateNewConfig()
{
    Logger::Out( "Creating new config file", "LuaConfig::CreateNewConfig", "config" );
    SetOption( "savegame_count", "0" );
    SaveConfig();
}

void LuaConfig::CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings )
{
    Logger::Out( "Create a new save file for " + playername, "LuaConfig::CreateNewSave", "config" );
    std::string savegameFile = playername + "-save.lua";
    int savegameCount = StringUtil::StringToInt( GetOption( "savegame_count" ) );
    SetOption( "savegame_" + StringUtil::IntToString(savegameCount + 1), savegameFile );
    m_currentSavegame = savegameFile;

    Logger::Out( "Savegame file is " + m_currentSavegame, "LuaConfig::CreateNewSave", "config" );

    for ( std::map<std::string, std::string>::iterator it = settings.begin();
            it != settings.end(); ++it )
    {
        std::pair<std::string, std::string> setting = (*it);
        SetSaveData( setting.first, setting.second );
    }
    SaveState();
}

void LuaConfig::DeleteCurrentSavefile()
{
    remove( m_currentSavegame.c_str() );
    m_currentSavegame = "";
}

void LuaConfig::SaveState()
{
    Logger::Out( "Write out save file \"" + m_currentSavegame + "\"", "LuaConfig::SaveState", "config" );

    std::ofstream out;
    out.open( ("savegames/" + m_currentSavegame).c_str() );

    out << "save = {" << std::endl;

    for ( std::map<std::string, std::string>::iterator it = m_saveData.begin();
        it != m_saveData.end(); ++it )
    {
        out << "\t" << it->first << " = \"" << it->second << "\"," << std::endl;

        Logger::Out( "\t" + it->first + " = " + it->second, "LuaConfig::SaveState", "config" );
    }

    out << "}" << std::endl;

    out.close();
}

bool LuaConfig::LoadState( const std::string& filename, const std::vector<std::string>& settings )
{
    m_currentSavegame = filename;

    if ( !LuaManager::LoadScript( "savegames/" + m_currentSavegame ) )
    {
        return false;
    }

    // Load in values to the key/value
    for ( unsigned int i = 0; i < settings.size(); i++ )
    {
        SetSaveData( settings[i], LuaManager::Savegame_GetData( settings[i] ) );
    }

    return true;
}

std::string LuaConfig::GetSaveData( const std::string& key )
{
    return m_saveData[ key ];
}

void LuaConfig::SetSaveData( const std::string& key, const std::string& val )
{
    Logger::Out( "Set save data \"" + key + "\" to value \"" + val + "\".", "LuaConfig::SetSaveData", "config" );
    m_saveData[ key ] = val;
}

std::string LuaConfig::GetSavegameName()
{
    return m_currentSavegame;
}

}

#endif
