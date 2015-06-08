#ifndef _CONFIGMANAGER
#define _CONFIGMANAGER

#include "interfaces/IConfig.hpp"

/*
This is for use to save config files and savegames
*/
namespace kuko
{

class ConfigManager
{
    public:
    // Setup
    static void Setup();
    static void Cleanup();

    // Configuration
    static void SaveConfig();
    static bool LoadConfig( const std::vector<std::string>& settings );
    static void SetOption( const std::string& key, const std::string& val );
    static std::string GetOption( const std::string& key );
    static int GetIntOption( const std::string& key );

    // Savegames
    static void CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings );
    static void SaveState();
    static bool LoadState( const std::string& filename, const std::vector<std::string>& settings );
    static std::string GetSaveData( const std::string& key );
    static void SetSaveData( const std::string& key, const std::string& val );
    static void DeleteCurrentSavefile();
    static std::string GetSavegameName();

    private:
    static IConfig* m_config;
};

}

#endif
