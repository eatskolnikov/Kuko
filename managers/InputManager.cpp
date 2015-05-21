// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "InputManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

SDL_Event InputManager::m_event;
std::map<CommandButton, TriggerInfo> InputManager::m_eventTriggered;
char InputManager::m_textInputBuffer[256];

void InputManager::Setup()
{
    m_textInputBuffer;
    ResetTriggers();
}

std::map<CommandButton, TriggerInfo> InputManager::GetTriggerInfo()
{
    return m_eventTriggered;
}

std::string InputManager::GetTextInputBuffer()
{
    return m_textInputBuffer;
}

void InputManager::Update()
{
    ResetTriggers();

    while ( SDL_PollEvent( &m_event ) != 0 )
    {
        // Clicking around in-game?
        if ( m_event.type == SDL_MOUSEBUTTONDOWN )
        {
        }

        // Taps for dealing with the menu
        else if ( m_event.type == SDL_MOUSEBUTTONUP )
        {
            if ( m_event.button.button == SDL_BUTTON_LEFT )
            {
                m_eventTriggered[ TAP ].down = true;
                m_eventTriggered[ TAP ].actionX = m_event.motion.x;
                m_eventTriggered[ TAP ].actionY = m_event.motion.y;
            }

            if ( m_event.button.button == SDL_BUTTON_RIGHT )
            {
                m_eventTriggered[ SECONDARY_TAP ].down = true;
                m_eventTriggered[ SECONDARY_TAP ].actionX = m_event.motion.x;
                m_eventTriggered[ SECONDARY_TAP ].actionY = m_event.motion.y;
            }
        }

        else if ( m_event.type == SDL_TEXTINPUT )
        {
            Logger::Out( "Received SDL_TEXTINPUT event", "InputManager::Update" );
            strcat( m_textInputBuffer, m_event.text.text );
            Logger::Out( "Value received: \"" + std::string(m_textInputBuffer) + "\"", "InputManager::Update" );
        }
    }

    // Check keyboard state
    const Uint8* keyStates = SDL_GetKeyboardState( NULL );
    if ( keyStates[ SDL_SCANCODE_UP ] )
    {
        m_eventTriggered [ MOVE_UP ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_DOWN ] )
    {
        m_eventTriggered [ MOVE_DOWN ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_LEFT ] )
    {
        m_eventTriggered [ MOVE_LEFT ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_RIGHT ] )
    {
        m_eventTriggered [ MOVE_RIGHT ].down = true;
    }
}

void InputManager::ResetTriggers()
{
    m_eventTriggered[ TAP ].down = false;
    m_eventTriggered[ SECONDARY_TAP ].down = false;
    m_eventTriggered[ MOVE_UP ].down = false;
    m_eventTriggered[ MOVE_DOWN ].down = false;
    m_eventTriggered[ MOVE_LEFT ].down = false;
    m_eventTriggered[ MOVE_RIGHT ].down = false;
    m_textInputBuffer[0] = '\0';
}

}
