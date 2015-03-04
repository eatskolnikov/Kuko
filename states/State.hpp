// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_STATE
#define _KUKO_STATE

#include "../managers/LuaManager.hpp"

#include "../base/Application.hpp"

#include <string>

namespace kuko
{

class State
{
    public:
    State( LuaManager* ptrLuaManager, const std::string& stateName, const std::string& scriptPath );
    virtual ~State();

    virtual void Setup();
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();

    protected:
    friend class StateManager;
    LuaManager* m_ptrLuaMgr;
    std::string m_stateName;
};

}

#endif
