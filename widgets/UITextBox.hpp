// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_TEXTBOX
#define _KUKO_TEXTBOX

#include <string>

#include "SDL_ttf.h"

#include "IWidget.hpp"
#include "../base/Sprite.hpp"

namespace kuko
{

class UITextBox : public IWidget
{
    public:
    UITextBox();
    virtual ~UITextBox() { ; }
    void Setup( const std::string& id, SDL_Rect position, SDL_Color bgColor, SDL_Color selectedColor, SDL_Color textColor, TTF_Font* font );
    void SetTextColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    void SetBackgroundColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
    virtual void Draw();
    virtual void Update();
    virtual void SetText( const std::string& text );
    virtual std::string GetText();
    virtual void AppendText( const std::string& text );
    virtual void SetActive( bool val );

    private:
    void GenerateTexture();

    std::string m_label;
    TTF_Font* m_font;
    Sprite m_sprite;
    SDL_Color m_textColor;
    SDL_Color m_bgColor;
    SDL_Color m_defaultBgColor;
    SDL_Color m_selectedBgColor;
};

}

#endif
