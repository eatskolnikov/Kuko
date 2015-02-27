// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "StateManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

StateManager::StateManager()
{
    m_ptrCurrentState = NULL;
    m_isDone = false;
}

void StateManager::Cleanup()
{
    for ( std::map< std::string, IState* >::iterator iter = m_lstStates.begin();
            iter != m_lstStates.end();
            ++iter )
    {
        if ( iter->second != NULL )
        {
            delete iter->second;
            iter->second = NULL;
        }
    }
}

bool StateManager::IsDone()
{
    return m_isDone;
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

void StateManager::UpdateCurrentState()
{
    if ( m_ptrCurrentState != NULL )
    {
        m_ptrCurrentState->Update();

        if ( m_ptrCurrentState->IsDone() )
        {
            std::string nextState = m_ptrCurrentState->GetNextState();
            Logger::Out( "Received state change signal, go to: " + nextState, "StateManager::UpdateCurrentState" );

            if ( nextState == "quit" )
            {
                m_isDone = true;
            }
            else if ( m_lstStates[ nextState ] != NULL )
            {
                SwitchState( nextState );
            }
            else
            {
                Logger::Error( "Error switching states: could not find state: " + nextState, "StateManager::UpdateCurrentState" );
            }
        }
    }
}

void StateManager::DrawCurrentState()
{
    if ( m_ptrCurrentState != NULL )
    {
        m_ptrCurrentState->Draw();
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
