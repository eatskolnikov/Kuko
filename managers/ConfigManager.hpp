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
    static void SaveConfig();
    static bool LoadConfig();
    static void SetConfig( const std::string& key, const std::string& val );

    private:
    static void CreateNewConfig();
    static std::map<std::string, std::string> m_settings;
};

}

#endif
