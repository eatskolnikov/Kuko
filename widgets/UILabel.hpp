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
    UILabel();
    virtual ~UILabel() { ; }
    void Setup( const std::string& id, const std::string& label, SDL_Rect position, bool centered, SDL_Color textColor, TTF_Font* font, const std::string& effect = "", int effectMax = 0 );
    void Setup( const std::string& id, const std::string& label, SDL_Rect position, bool centered, SDL_Color textColor, TTF_Font* font, const std::string& effect, int effectMax, bool useShadow, SDL_Color shadowColor, int shadowOffsetX, int shadowOffsetY );
    void SetColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    void SetShadowColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    virtual void Draw();
    virtual void Update();
    void ChangeText( const std::string& text );

    protected:
    // std::string m_id;
    // SDL_Rect m_position;

    void GenerateTexture();

    std::string m_label;
    TTF_Font* m_font;
    Sprite m_sprite;
    Sprite m_shadowSprite;
    SDL_Color m_color;
    SDL_Color m_shadowColor;
    bool m_centered;
    bool m_useShadow;
    int m_shadowOffsetX;
    int m_shadowOffsetY;
    std::string m_effect;
    int m_effectTimer;
    int m_effectMax;
};

}

#endif

