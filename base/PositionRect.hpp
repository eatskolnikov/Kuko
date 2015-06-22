#ifndef _KUKO_POSITIONRECT
#define _KUKO_POSITIONRECT

namespace kuko
{

class IntRect
{
    public:
    int x, y, w, h;
    IntRect() { ; }
    IntRect( int x, int y, int w, int h )
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    SDL_Rect ToSDLRect() const
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
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

class FloatRect
{
    public:
    float x, y, w, h;
    FloatRect() { ; }
    FloatRect( float x, float y, float w, float h )
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
