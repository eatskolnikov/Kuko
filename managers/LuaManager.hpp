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

        static void LoadScript( const std::string& path );

        static std::string Language_GetText( const std::string& key );

        private:
        static lua_State* m_state;

        static int m_args;
        static void Lua_ChooseFunction( const std::string& name );
        static void Lua_PushString( const std::string& value );
        static std::string Lua_GetStringResult();
    };
}

#endif
