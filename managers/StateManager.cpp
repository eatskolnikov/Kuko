// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "StateManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

StateManager::StateManager()
{
    m_ptrCurrentState = NULL;
}

void StateManager::Setup()
{
}

void StateManager::Cleanup()
{
}

void StateManager::Run()
{
    bool done = false;
    while ( !done )
    {
        RunCurrentState();

        std::string nextState = m_ptrCurrentState->GetNextState();
        if ( m_lstStates[ nextState ] != NULL )
        {
            // Change state
            SwitchState( nextState );
        }
        else
        {
            // Default - exit
            done = true;
        }
    }
}

void StateManager::PushState( const std::string& title, IState* ptrState )
{
    m_lstStates.insert(
        std::pair< std::string, IState* >(
            title,
            ptrState
        ) );
}

void StateManager::SwitchState( const std::string& key )
{
    Logger::Out( "Switch state to \"" + key + "\"", "StateManager::SwitchState" );
    // Clean the current state
    CleanCurrentState();

    // Initialize the next stat,
    m_ptrCurrentState = m_lstStates[ key ];
    m_ptrCurrentState->Setup();
}

void StateManager::RunCurrentState()
{
    if ( m_ptrCurrentState != NULL )
    {
        m_ptrCurrentState->Main();
    }
}

void StateManager::CleanCurrentState()
{
    if ( m_ptrCurrentState != NULL )
    {
        m_ptrCurrentState = NULL;
    }
}

}
