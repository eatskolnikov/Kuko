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
    virtual ~UILabel() { ; }
    void Setup( const std::string& id, const std::string& label, SDL_Rect position, SDL_Color textColor, TTF_Font* font );
    void SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    virtual void Draw();

    protected:
    // std::string m_id;
    // SDL_Rect m_position;

    void GenerateTexture();

    std::string m_label;
    TTF_Font* m_font;
    Sprite m_sprite;
    SDL_Color m_color;
};

}

#endif

