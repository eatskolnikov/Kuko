// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "LuaManager.hpp"
#include "../utilities/Logger.hpp"

namespace kuko
{

lua_State* LuaManager::m_state;
int LuaManager::m_args;

void LuaManager::Setup()
{
    m_state = luaL_newstate();
    luaL_openlibs( m_state );
    // Load required scripts
    // TODO: Possibly a problem due to project path
    LoadScript( "Kuko/scripts/Language.lua" );
}

void LuaManager::Cleanup()
{
    lua_close( m_state );
}

void LuaManager::LoadScript( const std::string& path )
{
    Logger::Out( "Load script \"" + path + "\"", "LuaManager::LoadScript" );
    luaL_dofile( m_state, path.c_str() );
}

std::string LuaManager::Language_GetText( const std::string& key )
{
    Logger::Out( "Get text for \"" + key + "\"", "LuaManager::Language_GetText" );
    Lua_ChooseFunction( "GetLanguageText" );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    Logger::Out( "Result: \"" + result + "\"", "LuaManager::Language_GetText" );
    return result;
}

void LuaManager::Lua_ChooseFunction( const std::string& name )
{
    lua_getglobal( m_state, name.c_str() );
    m_args = 0;
}

void LuaManager::Lua_PushString( const std::string& value )
{
    lua_pushstring( m_state, "menu_play" );
    m_args++;
}

std::string LuaManager::Lua_GetStringResult()
{
    lua_call( m_state, m_args, 1 );
    std::string text = (std::string)lua_tostring( m_state, -1 );
    lua_pop( m_state, 1 );
    return text;
}

}
