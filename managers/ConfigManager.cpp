#include "ConfigManager.hpp"

namespace kuko
{

void ConfigManager::LoadConfig()
{
    LuaManager::LoadScript( "config.lua" );
}

}
