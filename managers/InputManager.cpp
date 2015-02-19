#include "InputManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

SDL_Event InputManager::m_event;
std::map<CommandButton, TriggerInfo> InputManager::m_eventTriggered;

void InputManager::Setup()
{
    ResetTriggers();
}

void InputManager::Cleanup()
{
}

std::map<CommandButton, TriggerInfo> InputManager::GetTriggerInfo()
{
    return m_eventTriggered;
}

void InputManager::Update()
{
    ResetTriggers();

    while ( SDL_PollEvent( &m_event ) != 0 )
    {
        if ( m_event.type == SDL_MOUSEBUTTONDOWN )
        {
            if ( m_event.button.button == SDL_BUTTON_LEFT )
            {
                m_eventTriggered[ TAP ].down = true;
                m_eventTriggered[ TAP ].actionX = m_event.motion.x;
                m_eventTriggered[ TAP ].actionY = m_event.motion.y;
            }
            else if ( m_event.button.button == SDL_BUTTON_RIGHT )
            {
                m_eventTriggered[ SECONDARY_TAP ].down = true;
                m_eventTriggered[ SECONDARY_TAP ].actionX = m_event.motion.x;
                m_eventTriggered[ SECONDARY_TAP ].actionY = m_event.motion.y;
            }
        }
    }
}

void InputManager::ResetTriggers()
{
    m_eventTriggered[ TAP ].down = false;
    m_eventTriggered[ SECONDARY_TAP ].down = false;
}

}
