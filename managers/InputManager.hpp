// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_INPUTMANAGER
#define _KUKO_INPUTMANAGER

#include <SDL.h>

#include <map>
#include <string>

#include "../base/PositionRect.hpp"

namespace kuko
{

// TODO: Add "registration" of keys for commands.
enum CommandButton { TAP, SECONDARY_TAP, MOUSE_DOWN, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, BACKSPACE, WINDOW_CLOSE  };

class TriggerInfo
{
    public:
    TriggerInfo() { timeout = 0; maxTimeout = 50; }

    bool down;
    int actionX, actionY;
    int timeout;
    int maxTimeout;
};

class InputManager
{
    public:
    static void Setup();
    static void Cleanup();

    static void Update();
    static void IgnoreMouseUntilButtonUp();

    static std::map<CommandButton, TriggerInfo> GetTriggerInfo();
    static std::string GetTextInputBuffer();
    static void SetTextBufferActive( bool val );

    static IntRect GetMousePosition();

    static std::string GetKeyHit();

    protected:
    static void ResetTriggers();

    static SDL_Event m_event;
    static std::map<CommandButton, TriggerInfo> m_eventTriggered;

    static char m_textInputBuffer[256];
    static std::string m_lastKeyHit;

    static bool m_enableTextInput;
};

}

#endif

