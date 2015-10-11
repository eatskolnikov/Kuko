// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "Character.hpp"
#include "../utilities/StringUtil.hpp"

namespace kuko
{
    Character::Character()
    {
        m_speed = 1;
        m_direction = 0;
        m_frame = 0;
    }

    float Character::GetSpeed()
    {
        return m_speed;
    }

    void Character::SetSpeed( float val )
    {
        m_speed = val;
    }

    void Character::Move( CardinalDirection direction )
    {
        switch( direction )
        {
            case N:     Move( 0, -1 );  break;
            case S:     Move( 0, 1 );   break;
            case E:     Move( 1, 0 );   break;
            case W:     Move( -1, 0 );  break;
            case NE:    Move( 1, -1 );  break;
            case NW:    Move( -1, -1 ); break;
            case SE:    Move( 1, 1 );   break;
            case SW:    Move( -1, 1 );  break;
        }
    }

    /*
    Horizontal: -1 (left), 0 (none), 1 (right)
    Vertical: -1 (up), 0 (none), 1 (down)
    */
    void Character::Move( int horizontal, int vertical )
    {
        m_position.x += horizontal * m_speed;
        m_position.y += vertical * m_speed;
        UpdateFrame();
        UpdateSprite();
    }

    FloatRect Character::PositionWhenMoved( int horizontal, int vertical )
    {
        FloatRect pos = m_position;
        pos.x += horizontal * m_speed;
        pos.y += vertical * m_speed;
        return pos;
    }


    void Character::SetupAnimation( float maxFrame, float animateSpeed )
    {
        m_maxFrame = maxFrame;
        m_animateSpeed = animateSpeed;
    }

    void Character::SetDirection( int direction )
    {
        m_direction = direction;
    }

    void Character::UpdateFrame()
    {
        m_frame += m_animateSpeed;
        if ( m_frame >= m_maxFrame )
        {
            m_frame = 0;
        }
    }

    void Character::UpdateSprite()
    {
        int width = m_sprite.frame.w;
        int height = m_sprite.frame.h;
        int filmstripX = floor( m_frame ) * width;
        int filmstripY = m_direction * height;

        BaseEntity::UpdateSprite();
        SetFrame( IntRect( filmstripX, filmstripY, width, height ) );
    }
}

