// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "../utilities/Logger.hpp"

#include "State.hpp"

#include <string>

namespace kuko
{

State::State( LuaManager* ptrLuaManager, const std::string& stateName, const std::string& scriptPath )
{
    Logger::Out( "begin", "State::State" );
    m_ptrLuaMgr = ptrLuaManager;
    m_stateName = stateName;
    m_ptrLuaMgr->LoadScript( scriptPath );
    Logger::Out( "Load prereqs", "State::State" );
    m_ptrLuaMgr->State_LoadRequiredScripts();
    Logger::Out( "Setup", "State::State" );
    m_ptrLuaMgr->State_Setup();
    Logger::Out( "end", "State::State" );
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
