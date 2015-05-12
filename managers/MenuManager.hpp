// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_MENUMANAGER
#define _KUKO_MENUMANAGER

#include "../base/Application.hpp"
#include "../widgets/UIButton.hpp"
#include "../widgets/UILabel.hpp"
#include "../widgets/UIImage.hpp"

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
    void ResetMouse();

    int GetCurrentPage();
    void SetCurrentPage( int val );
    void NextPage();

    protected:
    std::map<std::string, UIImage*> m_images;
    std::map<std::string, UILabel*> m_labels;
    std::map<std::string, UIButton*> m_buttons;
    std::string m_currentMenu;
    bool m_mouseDown;
    int m_currentPage;
    int m_maxPages;
};

}

#endif
