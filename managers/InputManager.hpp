// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _INPUTMANAGER
#define _INPUTMANAGER

#include <SDL.h>

#include <map>

namespace kuko
{

enum CommandButton { TAP, SECONDARY_TAP };

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

    static std::map<CommandButton, TriggerInfo> GetTriggerInfo();

    protected:
    static void ResetTriggers();

    static SDL_Event m_event;
    static std::map<CommandButton, TriggerInfo> m_eventTriggered;
};

}

#endif

