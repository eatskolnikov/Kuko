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
    UIImage();
    virtual ~UIImage() { ; }
    void Setup( const std::string& id, FloatRect position, SDL_Texture* ptrTexture );
    void SetColor( SDL_Color color );
    virtual void Draw();
    virtual void Update();
    void SetFrame( IntRect fr );
    IntRect GetFrame();
    void SetTexture( SDL_Texture* ptrTexture );
    void SetPosition( const IntRect& pos );
    void SetPosition( float x, float y, float w, float h );

    protected:
    // std::string m_id;
    // SDL_Rect m_position;
    Sprite m_background;
    bool m_primitiveBackground;
    SDL_Color m_color;
};

}

#endif

