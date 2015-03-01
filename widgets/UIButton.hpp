// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_BUTTON
#define _KUKO_BUTTON

#include "SDL_ttf.h"

#include "IWidget.hpp"
#include "UIImage.hpp"
#include "UILabel.hpp"

namespace kuko
{

// Button = Image + Label, label relatively positioned based on widget origin?
class UIButton : public IWidget
{
    public:
    virtual ~UIButton() { ; }
    void Setup( const std::string& id, const std::string& text, SDL_Rect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, int padding = 0 );
    void Setup( const std::string& id, const std::string& text, SDL_Rect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, SDL_Rect padding );
    void Draw();
    bool IsTriggered( int actionX, int actionY );
    // SDL_Rect GetPosition();

    protected:
    UIImage m_background;
    UILabel m_text;
    // Label
    // std::string m_id;
    // SDL_Rect m_position;
};

}

#endif
