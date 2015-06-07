#ifndef _CONFIGMANAGER
#define _CONFIGMANAGER

#include <string>
#include <map>
#include <vector>

#include "LuaManager.hpp"

/*
This is for use to save config files and savegames
*/
namespace kuko
{

class ConfigManager
{
    public:
    // Configuration
    static void SaveConfig();
    static bool LoadConfig( const std::vector<std::string>& settings );
    static void SetOption( const std::string& key, const std::string& val );
    static std::string GetOption( const std::string& key );

    // Savegames
    static void CreateNewSave( const std::string& playername, const std::map<std::string, std::string>& settings );
    static void SaveState();
    static bool LoadState( const std::string& filename );
    static std::string GetSaveData( const std::string& key );
    static void SetSaveData( const std::string& key, const std::string& val );
    static void DeleteCurrentSavefile();
    static std::string GetSavegameName();

    private:
    // Configuration
    static void CreateNewConfig();
    static std::map<std::string, std::string> m_settings;

    // Savegames
    static std::map<std::string, std::string> m_saveData;
    static std::string m_currentSavegame;
};

}

#endif
