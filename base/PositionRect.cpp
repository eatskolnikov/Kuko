#include "PositionRect.hpp"

namespace kuko
{

bool operator==( IntRect& a, IntRect& b )
{
    return ( a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h );
}

bool operator!=( IntRect& a, IntRect& b )
{
    return ( a.x != b.x || a.y != b.y || a.w != b.w || a.h != b.h );
}


bool operator==( FloatRect& a, FloatRect& b )
{
    return ( a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h );
}

bool operator!=( FloatRect& a, FloatRect& b )
{
    return ( a.x != b.x || a.y != b.y || a.w != b.w || a.h != b.h );
}

}
