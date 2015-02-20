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
    void Setup( const std::string& id, const std::string& text, int posX, int posY, int width, int height,
        SDL_Texture* ptrTexture, SDL_Color textColor, TTF_Font* font );
    void Draw();
    bool IsTriggered( int actionX, int actionY );

    protected:
    UIImage m_background;
    UILabel m_text;
    // Label
    // std::string m_id;
    // SDL_Rect m_position;
};

}

#endif
