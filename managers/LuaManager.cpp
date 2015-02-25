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
    LoadScript( "Kuko/scripts/Menu.lua" );
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

void LuaManager::Lua_ChooseFunction( const std::string& name )
{
    lua_getglobal( m_state, name.c_str() );
    m_args = 0;
}

void LuaManager::Lua_PushString( const std::string& value )
{
    lua_pushstring( m_state, value.c_str() );
    m_args++;
}

void LuaManager::Lua_PushInt( int value )
{
    lua_pushnumber( m_state, value );
    m_args++;
}

std::string LuaManager::Lua_GetStringResult()
{
    lua_call( m_state, m_args, 1 );
    std::string text = (std::string)lua_tostring( m_state, -1 );
    lua_pop( m_state, 1 );
    return text;
}

int LuaManager::Lua_GetIntResult()
{
    lua_call( m_state, m_args, 1 );
    int result = (int)lua_tonumber( m_state, -1 );
    lua_pop( m_state, 1 );
    return result;
}

std::string LuaManager::Language_GetText( const std::string& key )
{
    Lua_ChooseFunction( "Language_GetText" );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

int LuaManager::Menu_GetElementCount()
{
    Lua_ChooseFunction( "Menu_GetElementCount" );
    int result = Lua_GetIntResult();
    return result;
}


std::string LuaManager::Menu_GetElementString( int index, const std::string& property )
{
    Lua_ChooseFunction( "Menu_GetElementProperty" );
    Lua_PushInt( index );
    Lua_PushString( property.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

int LuaManager::Menu_GetElementInt( int index, const std::string& property )
{
    Lua_ChooseFunction( "Menu_GetElementProperty" );
    Lua_PushInt( index );
    Lua_PushString( property.c_str() );
    int result = Lua_GetIntResult();
    return result;
}


}