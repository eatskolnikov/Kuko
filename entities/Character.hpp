// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_CHARACTER
#define _KUKO_CHARACTER

#include "BaseEntity.hpp"

namespace kuko
{

//    Character class is for entities that have stuff like
//    Animation, movement, derivates for player and npc would have
//    User input / AI decision making
class Character : public BaseEntity
{
    public:
    virtual void Setup();
    virtual void Cleanup();

    virtual void Update();
    virtual void Draw();

    protected:
    //std::string m_id;
    //SDL_Rect m_position;
    //Sprite m_sprite;

    //void UpdateSprite();
};

}

#endif
