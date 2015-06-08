#include "LualessConfig.hpp"

#ifdef NOLUA

#include "../utilities/StringUtil.hpp"
#include "../utilities/Logger.hpp"

#include <fstream>

namespace kuko
{

bool LualessConfig::LoadConfig( const std::vector<std::string>& settings )
{
    std::ifstream infile( "config.agordo" );
    if ( !infile.good() )
    {
        CreateNewConfig();
        return false;
    }

    std::string key;
    std::string value;
    while ( infile >> key )
    {
        // Pull the key & value and store it.
        value = "";
        infile >> value;
        SetOption( key, value );
    }

    return true;
}

void LualessConfig::SetOption( const std::string& key, const std::string& val )
{
    Logger::Out( "Set config option \"" + key + "\" to value \"" + val + "\".", "LualessConfig::SetOption", "config" );
    m_settings[ key ] = val;
}

std::string LualessConfig::GetOption( const std::string& key )
{
    return m_settings[ key ];
}

void LualessConfig::SaveConfig()
{
    Logger::Out( "Write out config file", "LualessConfig::SaveConfig", "config" );

    std::ofstream out;
    out.open( "config.agordo" );

    for ( std::map<std::string, std::string>::iterator it = m_settings.begin();
        it != m_settings.end(); ++it )
    {
        out << it->first << " " << it->second << std::endl;
    }

    out.close();
}

void LualessConfig::CreateNewConfig()
{
    Logger::Out( "Creating new config file", "LualessConfig::CreateNewConfig", "config" );
    SetOption( "savegame_count", "0" );
    SetOption( "language", "english" );
    SaveConfig();
}

void LualessConfig::CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings )
{
    Logger::Out( "Create a new save file for " + playername, "LualessConfig::CreateNewSave", "config" );
    std::string savegameFile = playername + "-save.ludo";
    int savegameCount = StringUtil::StringToInt( GetOption( "savegame_count" ) );
    SetOption( "savegame_" + StringUtil::IntToString(savegameCount + 1), savegameFile );
    m_currentSavegame = savegameFile;

    Logger::Out( "Savegame file is " + m_currentSavegame, "LualessConfig::CreateNewSave", "config" );

    for ( std::map<std::string, std::string>::iterator it = settings.begin();
            it != settings.end(); ++it )
    {
        std::pair<std::string, std::string> setting = (*it);
        SetSaveData( setting.first, setting.second );
    }
    SaveState();
}

void LualessConfig::DeleteCurrentSavefile()
{
    remove( m_currentSavegame.c_str() );
    m_currentSavegame = "";
}

void LualessConfig::SaveState()
{
    Logger::Out( "Write out save file \"" + m_currentSavegame + "\"", "LualessConfig::SaveState", "config" );

    std::ofstream out;
    out.open( ("savegames/" + m_currentSavegame).c_str() );

    for ( std::map<std::string, std::string>::iterator it = m_saveData.begin();
        it != m_saveData.end(); ++it )
    {
        out << it->first << " " << it->second << std::endl;

        Logger::Out( "\t" + it->first + " = " + it->second, "LualessConfig::SaveState", "config" );
    }

    out.close();
}

bool LualessConfig::LoadState( const std::string& filename, const std::vector<std::string>& settings )
{
    m_currentSavegame = filename;
    std::string path = "savegames/" + m_currentSavegame;
    std::ifstream infile( path.c_str() );
    if ( !infile.good() )
    {
        return false;
    }

    std::string key;
    std::string value;
    while ( infile >> key )
    {
        // Pull the key & value and store it.
        value = "";
        infile >> value;
        SetSaveData( key, value );
    }

    return true;
}

std::string LualessConfig::GetSaveData( const std::string& key )
{
    return m_saveData[ key ];
}

void LualessConfig::SetSaveData( const std::string& key, const std::string& val )
{
    Logger::Out( "Set save data \"" + key + "\" to value \"" + val + "\".", "LualessConfig::SetSaveData", "config" );
    m_saveData[ key ] = val;
}

std::string LualessConfig::GetSavegameName()
{
    return m_currentSavegame;
}

}

#endif
