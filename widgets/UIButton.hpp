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
    UIButton();
    virtual ~UIButton() { ; }
    void Setup( const std::string& id, FloatRect position, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor );

    void Setup( const std::string& id, int x, int y, int w, int h, bool centered, SDL_Texture* ptrTexture, SDL_Color buttonColor );

    void Setup( const std::string& id, const std::string& text, FloatRect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, int padding = 0 );

    void Setup( const std::string& id, const std::string& text, FloatRect position, bool centered,
        SDL_Texture* ptrTexture, SDL_Color buttonColor, SDL_Color textColor, TTF_Font* font, FloatRect padding );

    void SetupAnimateEffect( const std::string& effectType, SDL_Texture* frame2, int effectMax );
    void Draw();
    void Update();
    bool IsTriggered( int actionX, int actionY );
    void SetFrame( IntRect fr );
    // SDL_Rect GetPosition();

    protected:
    UIImage m_background[2];
    UILabel m_text;
    bool m_useText;
    std::string m_effect;
    int m_effectTimer;
    int m_effectMax;
    // Label
    // std::string m_id;
    // SDL_Rect m_position;
};

}

#endif
