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
    LoadScript( "Kuko/scripts/Map.lua" );
    LoadScript( "Kuko/scripts/Config.lua" );
}

void LuaManager::Cleanup()
{
    lua_close( m_state );
}

bool LuaManager::LoadScript( const std::string& path )
{
    Logger::Out( "Load script \"" + path + "\"", "LuaManager::LoadScript" );
    if ( luaL_dofile( m_state, path.c_str() ) )
    {
        std::string status = lua_tostring( m_state, -1 );
        Logger::Out( "Script loading state: " + status );
        return false;   // TODO: is this right?
    }
    return true;
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

void LuaManager::Lua_RunVoidFunction()
{
    // No Result to pop
    lua_call( m_state, m_args, 1 );
}

std::string LuaManager::Language_GetText( const std::string& key )
{
    Lua_ChooseFunction( "Language_GetText" );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

std::string LuaManager::Language_GetText( const std::string& langType, const std::string& key )
{
    Lua_ChooseFunction( "Language_GetTextFromLanguage" );
    Lua_PushString( key.c_str() );
    Lua_PushString( langType.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

std::string LuaManager::Language_GetSuggestedFont()
{
    Lua_ChooseFunction( "Language_GetSuggestedFont" );
    std::string result = Lua_GetStringResult();
    return result;
}

std::string LuaManager::Language_GetSpecialField( const std::string& langType, const std::string& field, const std::string& key )
{
    Lua_ChooseFunction( "Language_GetSpecialField" );
    Lua_PushString( langType.c_str() );
    Lua_PushString( field.c_str() );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

std::string LuaManager::Language_GetSpecialField( const std::string& langType, const std::string& field, int key )
{
    Lua_ChooseFunction( "Language_GetSpecialField" );
    Lua_PushString( langType.c_str() );
    Lua_PushString( field.c_str() );
    Lua_PushInt( key );
    std::string result = Lua_GetStringResult();
    return result;
}

int LuaManager::Language_GetSpecialFieldCount( const std::string& langType, const std::string& field )
{
    Lua_ChooseFunction( "Language_GetSpecialFieldCount" );
    Lua_PushString( langType.c_str() );
    Lua_PushString( field.c_str() );
    int result = Lua_GetIntResult();
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

int LuaManager::Menu_GetOptionInt( const std::string& property )
{
    Lua_ChooseFunction( "Menu_GetOptionProperty" );
    Lua_PushString( property.c_str() );
    int result = Lua_GetIntResult();
    return result;
}

int LuaManager::Map_GetWidth()
{
    Lua_ChooseFunction( "Map_GetWidth" );
    int result = Lua_GetIntResult();
    return result;
}

int LuaManager::Map_GetHeight()
{
    Lua_ChooseFunction( "Map_GetHeight" );
    int result = Lua_GetIntResult();
    return result;
}

int LuaManager::Map_GetTileType( int index )
{
    // Don't forget that Lua arrays begin at 1.
    Lua_ChooseFunction( "Map_GetTileType" );
    Lua_PushInt( index+1 );
    int result = Lua_GetIntResult();
    return result-1;
}

int LuaManager::Map_GetTilesetWidth()
{
    Lua_ChooseFunction( "Map_GetTilesetWidth" );
    int result = Lua_GetIntResult();
    return result;
}

int LuaManager::Map_GetTileWidth()
{
    Lua_ChooseFunction( "Map_GetTileWidth" );
    int result = Lua_GetIntResult();
    return result;
}

int LuaManager::Map_GetCustomPropertyCount()
{
    Lua_ChooseFunction( "Map_GetTilePropertyCount" );
    int result = Lua_GetIntResult();
    return result;
}

bool LuaManager::Map_GetTileSolidity( int index )
{
    // Index is the index of "tiles who have special properties"
    Lua_ChooseFunction( "Map_GetCustomTileSolidity" );
    Lua_PushInt( index+1 );
    std::string result = Lua_GetStringResult();
    return ( result == "1" ) ? true : false;
}

int LuaManager::Map_GetTileIndex( int index )
{
    Lua_ChooseFunction( "Map_GetCustomTileIndex" );
    Lua_PushInt( index+1 );
    int result = Lua_GetIntResult();
    return result; // TODO: Double check the offset for this, not sure
}

std::string LuaManager::Config_GetOption( const std::string& key )
{
    Lua_ChooseFunction( "Config_GetOption" );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

std::string LuaManager::Savegame_GetData( const std::string& key )
{
    Lua_ChooseFunction( "Savegame_GetData" );
    Lua_PushString( key.c_str() );
    std::string result = Lua_GetStringResult();
    return result;
}

}
