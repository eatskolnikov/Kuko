#ifndef _CONFIGMANAGER
#define _CONFIGMANAGER

#include <string>

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
    static void LoadConfig();

    private:
};

}

#endif
