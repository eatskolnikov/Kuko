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
    bool IsButtonClicked( const std::string& key, float mouseX, float mouseY );
    void CheckTextboxClick( float mouseX, float mouseY );
    void ResetMouse();
    void HandleUIInput();

    void SetTextEditing( bool turnOn );
    void AppendToActiveTextBox( const std::string& text );
    void RemoveLastCharacterOfActiveTextBox();
    std::string GetTextboxValue( const std::string& key );
    void UpdateLabelText( const std::string& id, const std::string& text );

    void AddLabel( const std::string& id, UILabel* label );
    void AddLabel( const std::string& id, const std::string& lbl, int x, int y, int width, int height, bool centered, SDL_Color textColor, TTF_Font* font );

    void AddButton( const std::string& id, UIButton* button );
    void AddButton( const std::string& id,SDL_Texture* ptrTexture,  int x, int y, int width, int height, bool centered, SDL_Color buttonColor, void (*Callback)(void) );

    void AddImage( const std::string& id, UIImage* image );
    void AddImage( const std::string& id, SDL_Texture* ptrTexture, int x, int y, int width, int height, bool centered, const std::string& effectName = "", int effectMax = 0 );

    void AddTextBox( const std::string& id, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color selectedColor, SDL_Color textColor, TTF_Font* font, int maxLength );

    int GetCurrentPage();
    void SetCurrentPage( int val );
    void NextPage();

    void OutputElementNames(); // debug

    protected:
    void LoadButton( int index );
    void LoadImage( int index );
    void LoadLabel( int index );
    void LoadTextbox( int index );

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
