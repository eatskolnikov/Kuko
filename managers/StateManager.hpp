// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _STATEMANAGER
#define _STATEMANAGER

#include "../states/IState.hpp"
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

    void PushState( const std::string& title, IState* ptrState );
    void SwitchState( const std::string& key );
    void RunCurrentState();

    void Run();

    private:
    void CleanCurrentState();

    std::map< std::string, IState* > m_lstStates;
    IState* m_ptrCurrentState;
};

}

#endif
