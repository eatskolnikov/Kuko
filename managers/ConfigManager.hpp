#ifndef _CONFIGMANAGER
#define _CONFIGMANAGER

#include <string>
#include <map>

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
    static bool LoadConfig();
    static void SetOption( const std::string& key, const std::string& val );
    static std::string GetOption( const std::string& key );

    // Savegames
    static void CreateNewSave( const std::string& filename );
    static void SaveState();
    static void LoadState( const std::string& filename );
    static std::string GetSaveData( const std::string& key );

    private:
    // Configuration
    static void CreateNewConfig();
    static std::map<std::string, std::string> m_settings;

    // Savegames
    static std::map<std::string, std::string> m_saveData;
};

}

#endif
