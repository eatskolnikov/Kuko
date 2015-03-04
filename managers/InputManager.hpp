// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_INPUTMANAGER
#define _KUKO_INPUTMANAGER

#include <SDL.h>

#include <map>

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
    void Setup();
    void Cleanup();

    void Update();

    std::map<CommandButton, TriggerInfo> GetTriggerInfo();

    protected:
    void ResetTriggers();

    SDL_Event m_event;
    std::map<CommandButton, TriggerInfo> m_eventTriggered;
};

}

#endif

