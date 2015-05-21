// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_INPUTMANAGER
#define _KUKO_INPUTMANAGER

#include <SDL.h>

#include <map>
#include <string>

namespace kuko
{

// TODO: Add "registration" of keys for commands.
enum CommandButton { TAP, SECONDARY_TAP, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

struct TriggerInfo
{
    bool down;
    int actionX, actionY;
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

    protected:
    static void ResetTriggers();

    static SDL_Event m_event;
    static std::map<CommandButton, TriggerInfo> m_eventTriggered;

    static char m_textInputBuffer[256];
};

}

#endif

