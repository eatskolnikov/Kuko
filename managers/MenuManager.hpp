// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_MENUMANAGER
#define _KUKO_MENUMANAGER

#include "../base/Application.hpp"
#include "../widgets/UIButton.hpp"
#include "../widgets/UILabel.hpp"
#include "../widgets/UIImage.hpp"
#include "../widgets/UITextBox.hpp"

#include <map>
#include <string>
#include <set>

namespace kuko
{

class MenuManager
{
    public:
    MenuManager();
    ~MenuManager();
    void SetupMenu( const std::string& path );
    void ClearMenu();
    void Draw();
    void Update();
    void Reload();
    bool IsButtonClicked( const std::string& key, int mouseX, int mouseY );
    void CheckTextboxClick( int mouseX, int mouseY );
    void ResetMouse();
    void SetTextEditing( bool turnOn );
    void AppendToActiveTextBox( const std::string& text );
    void RemoveLastCharacterOfActiveTextBox();
    std::string GetTextboxValue( const std::string& key );
    void UpdateLabelText( const std::string& id, const std::string& text );

    void AddLabel( const std::string& id, UILabel* label );
    void AddLabel( const std::string& id, const std::string& lbl, int x, int y, int width, int height, bool centered, SDL_Color textColor, TTF_Font* font );

    void AddButton( const std::string& id, UIButton* button );
    //void AddButton( const std::string& id,, Effect effects );

    void AddImage( const std::string& id, UIImage* image );
    void AddImage( const std::string& id, SDL_Texture* ptrTexture, int x, int y, int width, int height, const std::string& effectName = "", int effectMax = 0 );

    int GetCurrentPage();
    void SetCurrentPage( int val );
    void NextPage();

    protected:
    std::map<std::string, UIImage*> m_images;
    std::map<std::string, UILabel*> m_labels;
    std::map<std::string, UIButton*> m_buttons;
    std::map<std::string, UITextBox*> m_textboxes;
    std::string m_currentMenu;
    bool m_mouseDown;
    int m_currentPage;
    int m_maxPages;
    UITextBox* m_activeTextbox;
};

}

#endif
