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
#include <functional>

namespace kuko
{

class MenuManager
{
    public:
    MenuManager();
    ~MenuManager();

    void LoadMenuScript( const std::string& path );
    void SetupMenu( const std::string& path );
    void BuildMenu();

    int AssetListSize();
    std::string AssetTitle( int index );
    std::string AssetPath( int index );

    void ClearMenu();
    void Draw();
    void Update();
    void Reload();

    bool IsButtonClicked( const std::string& key, float mouseX, float mouseY );
    std::string GetButtonClicked( float mouseX, float mouseY );
    bool CheckTextboxClick( float mouseX, float mouseY );
    void CheckButtonClick( float mouseX, float mouseY );
    void DeactivateCurrentTextbox();

    void HandleUIInput();

    void SetTextEditing( bool turnOn );
    void AppendToActiveTextBox( const std::string& text );
    void RemoveLastCharacterOfActiveTextBox();
    std::string GetTextboxValue( const std::string& key );
    void SetTextboxValue( const std::string& key, const std::string& value );
    void UpdateLabelText( const std::string& id, const std::string& text );

    void AddLabel( const std::string& id, UILabel* label );
    void AddLabel( const std::string& id, const std::string& lbl, int x, int y, int width, int height, bool centered, SDL_Color textColor, TTF_Font* font );
    UILabel* GetLabel( const std::string& name );

    void AddButton( const std::string& id, UIButton* button );
    void AddButton( const std::string& id,SDL_Texture* ptrTexture,  int x, int y, int width, int height, bool centered, SDL_Color buttonColor );
    UIButton* GetButton( const std::string& name );
    std::map<std::string, UIButton*>& GetButtons();

    void AddImage( const std::string& id, UIImage* image );
    void AddImage( const std::string& id, SDL_Texture* ptrTexture, int x, int y, int width, int height, bool centered, const std::string& effectName = "", int effectMax = 0 );

    void AddTextBox( const std::string& id, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color selectedColor, SDL_Color textColor, TTF_Font* font, int maxLength );

    int GetCurrentPage();
    void SetCurrentPage( int val );
    void NextPage();

    void ToggleMouse( bool active );
    bool IsMouseActive();

    void OutputElementNames(); // debug

    void RemoveButton( const std::string& key );
    void RemoveLabel( const std::string& key );

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
    int m_currentPage;
    int m_maxPages;
    UITextBox* m_activeTextbox;
};

}

#endif
