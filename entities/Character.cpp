// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "Character.hpp"

namespace kuko
{
    Character::Character()
    {
    }

    void Character::SetPosition( int x, int y )
    {
        m_position.x = x;
        m_position.y = y;
        UpdateSprite();
    }
}

