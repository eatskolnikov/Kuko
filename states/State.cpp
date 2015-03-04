// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "State.hpp"

#include <string>

namespace kuko
{

State::State( LuaManager* ptrLuaManager, const std::string& objName, const std::string& scriptPath )
{
    m_ptrLuaMgr = ptrLuaManager;
    m_stateName = objName;
    m_ptrLuaMgr->LoadScript( scriptPath );
}

State::~State()
{
}



void State::Setup()
{
}

void State::Cleanup()
{
}

void State::Update()
{
}

void State::Draw()
{
}


}
