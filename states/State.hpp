// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_STATE
#define _KUKO_STATE

#include "../managers/LuaManager.hpp"
#include "../managers/InputManager.hpp"

#include "../base/Application.hpp"
#include "../entities/BaseEntity.hpp"

#include <string>
#include <vector>

namespace kuko
{

class State
{
    public:
    State( LuaManager* ptrLuaManager, ImageManager* ptrImageManager, const std::string& stateName, const std::string& scriptPath );
    virtual ~State();

    virtual void Setup();
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();

    virtual void HandleInput( std::map<kuko::CommandButton, kuko::TriggerInfo> input );

    protected:
    friend class StateManager;
    LuaManager* m_ptrLuaMgr;
    std::string m_stateName;
    std::vector<BaseEntity*> m_lstEntities;
};

}

#endif
