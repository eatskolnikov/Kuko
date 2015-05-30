#ifndef _KUKO_POSITIONRECT
#define _KUKO_POSITIONRECT

namespace kuko
{

class PositionRect
{
    public:
    float x, y, w, h;
    PositionRect() { ; }
    PositionRect( float x, float y, float w, float h )
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
};

}

#endif
