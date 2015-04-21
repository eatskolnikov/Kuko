#ifndef _CONFIGMANAGER
#define _CONFIGMANAGER

#include <fstream>
#include <string>

/*
This is for use to save config files and savegames
*/
namespace kuko
{

class ConfigManager
{
    public:
    void SaveConfig();
    void LoadConfig();

    private:
};

}

#endif
