// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_IMAGE
#define _KUKO_IMAGE

#include "IWidget.hpp"
#include "../base/Sprite.hpp"

namespace kuko
{

// Specify a sprite for the background. Otherwise, default to colored rectangle
class UIImage : public IWidget
{
    public:
    void Setup( const std::string& id, SDL_Rect position, SDL_Texture* ptrTexture );
    void SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    virtual void Draw();

    protected:
    // std::string m_id;
    // SDL_Rect m_position;
    Sprite m_background;
    bool m_primitiveBackground;
    Uint8 r, g, b, a;
};

}

#endif

