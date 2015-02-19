// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _ISTATE
#define _ISTATE

#include "../base/Application.hpp"

#include <string>

namespace kuko
{

class IState
{
    public:
    virtual ~IState() { ; }
    IState() { m_isDone = false; m_isSetup = false; m_gotoState = ""; }

    virtual void Setup() = 0;
    virtual void Cleanup() = 0;

    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual std::string GetNextState() { return m_gotoState; }
    virtual bool IsDone() { return m_gotoState != ""; }

    protected:
    bool m_isDone;
    bool m_isSetup;
    std::string m_gotoState;

    friend class StateManager;
};

}

#endif
