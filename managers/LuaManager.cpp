// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "LuaManager.hpp"
#include "../utilities/Logger.hpp"

#include <lua.hpp>

//extern "C"{
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//}

namespace kuko
{

void LuaManager::Test()
{
    Logger::Out( "\n\nTest Lua" );

    lua_State* L = luaL_newstate();
    luaL_openlibs( L );

    luaL_dofile(L, "temp.lua");

    // Call function in sample file
    lua_getglobal( L, "add" );
    lua_pushnumber(L, 2);
    lua_pushnumber(L, 3);
    lua_call(L, 2, 1);
    int sum = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    Logger::Out( "Result: " + Logger::IntToString( sum ) );

    lua_close( L );

    Logger::Out( "Lua done\n\n" );
}

}
