// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#ifndef _KUKO_LUAMANAGER
#define _KUKO_LUAMANAGER

#include <lua.hpp>

#include <string>

namespace kuko
{
    class LuaManager
    {
        public:
        static void Setup();
        static void Cleanup();

        protected:
        static bool LoadScript( const std::string& path );

        // Language Functions
        static std::string Language_GetText( const std::string& key );
        static std::string Language_GetText( const std::string& langType, const std::string& key );
        static std::string Language_GetSuggestedFont();

        // Menu Functions
        static int Menu_GetElementCount();
        static std::string Menu_GetElementString( int index, const std::string& property );
        static int Menu_GetElementInt( int index, const std::string& property );
        static int Menu_GetOptionInt( const std::string& property );

        // Map Functions
        static int Map_GetWidth();
        static int Map_GetHeight();
        static int Map_GetTileType( int index );
        static int Map_GetTilesetWidth();
        static int Map_GetTileWidth();
        static int Map_GetCustomPropertyCount();
        static bool Map_GetTileSolidity( int index );
        static int Map_GetTileIndex( int index );

        // Config Functions
        static std::string Config_GetOption( const std::string& key );
        static std::string Savegame_GetData( const std::string& key );

        static lua_State* m_state;

        static int m_args;
        static void Lua_ChooseFunction( const std::string& name );
        static void Lua_PushString( const std::string& value );
        static void Lua_PushInt( int value );
        static std::string Lua_GetStringResult();
        static int Lua_GetIntResult();
        static void Lua_RunVoidFunction();

        friend class LanguageManager;
        friend class MapManager;
        friend class MenuManager;
        friend class ConfigManager;
    };
}

#endif
