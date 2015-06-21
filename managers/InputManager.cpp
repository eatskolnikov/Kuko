// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "InputManager.hpp"

#include "../utilities/Logger.hpp"

namespace kuko
{

SDL_Event InputManager::m_event;
std::map<CommandButton, TriggerInfo> InputManager::m_eventTriggered;
char InputManager::m_textInputBuffer[256];
bool InputManager::m_enableTextInput;

void InputManager::Setup()
{
    m_textInputBuffer;
    m_enableTextInput = false;
    ResetTriggers();
}

std::map<CommandButton, TriggerInfo> InputManager::GetTriggerInfo()
{
    return m_eventTriggered;
}

void InputManager::SetTextBufferActive( bool val )
{
    m_enableTextInput = val;
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

        // Window Events
        else if ( m_event.type == SDL_QUIT )
        {
            m_eventTriggered[ WINDOW_CLOSE ].down = true;
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
            // type, timestamp, windowID, text
            // https://wiki.libsdl.org/SDL_TextInputEvent
            std::string value = m_event.text.text;
            Logger::Out( "Received SDL_TEXTINPUT event: " + value, "InputManager::Update" );
            if ( m_enableTextInput )
            {
                strcat( m_textInputBuffer, m_event.text.text );
                Logger::Out( "Value received: \"" + std::string( m_textInputBuffer ) + "\"", "InputManager::Update" );
            }
            else if ( value == "w" )
            {
                Logger::Out( "Key w", "InputManager::Update" );
                m_eventTriggered [ MOVE_UP ].down = true;
            }
            else if ( value == "s" )
            {
                Logger::Out( "Key s", "InputManager::Update" );
                m_eventTriggered [ MOVE_DOWN ].down = true;
            }
            else if ( value == "a" )
            {
                Logger::Out( "Key a", "InputManager::Update" );
                m_eventTriggered [ MOVE_LEFT ].down = true;
            }
            else if ( value == "d" )
            {
                Logger::Out( "Key d", "InputManager::Update" );
                m_eventTriggered [ MOVE_RIGHT ].down = true;
            }
        }

        else if ( m_event.type == SDL_TEXTEDITING )
        {
            // type, timestamp, windowID, text, start, length
            // https://wiki.libsdl.org/SDL_TextEditingEvent
            Logger::Out( "Received SDL_TEXTEDITING event", "InputManager::Update" );
            char blah[256];
            strcat( blah, m_event.text.text );
            Logger::Out( "Value received: \"" + std::string( blah ) + "\"", "InputManager::Update" );
        }
    }

    // Check keyboard state
    const Uint8* keyStates = SDL_GetKeyboardState( NULL );
    if ( keyStates[ SDL_SCANCODE_UP ] || keyStates[ SDLK_w ] )
    {
        m_eventTriggered [ MOVE_UP ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_DOWN ] || keyStates[ SDLK_s ] )
    {
        m_eventTriggered [ MOVE_DOWN ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_LEFT ] || keyStates[ SDLK_w ] )
    {
        m_eventTriggered [ MOVE_LEFT ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_RIGHT ] || keyStates[ SDLK_d ] )
    {
        m_eventTriggered [ MOVE_RIGHT ].down = true;
    }
    if ( keyStates[ SDL_SCANCODE_BACKSPACE ] && m_eventTriggered [ BACKSPACE ].timeout == 0 )
    {
        m_eventTriggered [ BACKSPACE ].down = true;
        m_eventTriggered [ BACKSPACE ].timeout = m_eventTriggered [ BACKSPACE ].maxTimeout;
    }

    // Handle timeouts
    if ( m_eventTriggered [ BACKSPACE ].timeout > 0 )
    {
        m_eventTriggered [ BACKSPACE ].timeout -= 1;
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
    m_eventTriggered[ WINDOW_CLOSE ].down = false;
    m_eventTriggered[ BACKSPACE ].down = false;
    m_textInputBuffer[0] = '\0';
}

}
