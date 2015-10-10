// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_CHARACTER
#define _KUKO_CHARACTER

#include "BaseEntity.hpp"

namespace kuko
{

//    Character class is for entities that have stuff like
//    Animation, movement, derivates for player and npc would have
//    User input / AI decision making
enum CardinalDirection { N, S, E, W, NE, NW, SE, SW };

class Character : public BaseEntity
{
    public:
    Character();
    float GetSpeed();
    void SetSpeed( float val );
    void Move( CardinalDirection direction );
    void Move( int horizontal, int vertical );
    void SetupAnimation( float maxFrame, float animateSpeed );
    void UpdateFrame();
    void SetDirection( int direction );

    protected:
    void UpdateSprite();

    float m_speed;
    float m_frame;
    float m_maxFrame;
    float m_animateSpeed;
    int m_direction;
};

}

#endif
