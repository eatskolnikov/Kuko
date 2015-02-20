// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LABEL
#define _KUKO_LABEL

#include <string>

#include "SDL_ttf.h"

#include "IWidget.hpp"
#include "../base/Sprite.hpp"

namespace kuko
{

class UILabel : public IWidget
{
    public:
    void Setup( const std::string& id, const std::string& label, TTF_Font* font,
    int posX, int posY, int width, int height,
        Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    void SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    virtual void Draw();

    protected:
    // std::string m_id;
    // SDL_Rect m_position;

    void GenerateTexture();

    std::string m_label;
    Uint8 r, g, b, a;
    TTF_Font* m_font;
    Sprite m_sprite;
    SDL_Color m_color;
};

}

#endif

