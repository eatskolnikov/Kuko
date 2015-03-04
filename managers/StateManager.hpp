// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_STATEMANAGER
#define _KUKO_STATEMANAGER

#include "../states/State.hpp"
#include "../base/Application.hpp"

#include <map>
#include <string>

namespace kuko
{

class StateManager
{
    public:
    StateManager();

    void Setup();
    void Cleanup();

    void PushState( const std::string& title, State* ptrState );
    void SwitchState( const std::string& key );
    void UpdateCurrentState();
    void DrawCurrentState();
    bool IsDone();

    private:
    bool m_isDone;
    void CleanCurrentState();

    std::map< std::string, State* > m_lstStates;
    State* m_ptrCurrentState;
};

}

#endif
