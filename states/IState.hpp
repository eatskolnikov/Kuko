// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_ISTATE
#define _KUKO_ISTATE

#include "../base/Application.hpp"
#include "../managers/InputManager.hpp"

#include <string>

namespace kuko
{

class IState
{
    public:
    virtual ~IState();
    IState();

    virtual void Setup() = 0;
    virtual void Cleanup() = 0;

    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual std::string GetNextState();
    virtual bool IsDone();

    protected:
    bool m_isDone;
    bool m_isSetup;
    std::string m_gotoState;

    friend class StateManager;
};

}

#endif
