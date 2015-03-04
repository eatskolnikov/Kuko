// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#ifndef _KUKO_LUAMANAGER
#define _KUKO_LUAMANAGER

#include <lua.hpp>

#include <string>
#include <vector>

namespace kuko
{
    class LuaManager
    {
        public:
        LuaManager();
        ~LuaManager();

        void Setup();
        void Cleanup();

        protected:
        void LoadScript( const std::string& path );

        // Language Functions
        std::string Language_GetText( const std::string& key );
        std::string Language_GetSuggestedFont();

        // Menu Functions
        int Menu_GetElementCount();
        std::string Menu_GetElementString( int index, const std::string& property );
        int Menu_GetElementInt( int index, const std::string& property );

        // Map Functions
        int Map_GetWidth();
        int Map_GetHeight();
        int Map_GetTileType( int index );
        int Map_GetTilesetWidth();
        int Map_GetTileWidth();
        int Map_GetCustomPropertyCount();
        bool Map_GetTileSolidity( int index );
        int Map_GetTileIndex( int index );

        // States
        void State_Setup();
        void State_LoadRequiredScripts();
        int State_GetEntityCount();
        std::string State_GetEntityName( int index );
        std::vector<int> State_GetEntityPosition( const std::string& name );
        std::string State_GetEntityTextureFile( const std::string& name );

        lua_State* m_state;

        int m_args;
        void Lua_ChooseFunction( const std::string& name );
        void Lua_PushString( const std::string& value );
        void Lua_PushInt( int value );
        std::string Lua_GetStringResult();
        std::vector<std::string> Lua_GetMultipleStringResult( int resultCount );
        std::vector<int> Lua_GetMultipleIntResult( int resultCount );
        int Lua_GetIntResult();
        void Lua_RunVoidFunction();

        friend class LanguageManager;
        friend class MapManager;
        friend class MenuManager;
        friend class State;
        friend class BaseEntity;
    };
}

#endif
