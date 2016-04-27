#include "IState.hpp"

namespace kuko
{

IState::~IState()
{
}

IState::IState()
{
    m_isDone = false;
    m_isSetup = false;
    m_gotoState = "";
}

void IState::Setup()
{
    m_gotoState = "";
}

void IState::Cleanup()
{
    m_gotoState = "";
}

std::string IState::GetNextState()
{
    return m_gotoState;
}

bool IState::IsDone()
{
    return m_gotoState != "";
}

};
