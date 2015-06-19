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

    SDL_Rect ToSDLRect() const
    {
        SDL_Rect rect;
        rect.x = int( x );
        rect.y = int( y );
        rect.w = int( w );
        rect.h = int( h );
        return rect;
    }

    void Set( SDL_Rect rect )
    {
        x = rect.x;
        y = rect.y;
        w = rect.w;
        h = rect.h;
    }
};

}

#endif
