// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_MENUMANAGER
#define _KUKO_MENUMANAGER

#include "../base/Application.hpp"
#include "../widgets/UIButton.hpp"
#include "../widgets/UILabel.hpp"
#include "../widgets/UIImage.hpp"

#include <map>
#include <string>

namespace kuko
{

class MenuManager
{
    public:
    ~MenuManager();
    void SetupMenu( const std::string& path );
    void ClearMenu();
    void Draw();
    void Reload();

    protected:
    std::map<std::string, UIImage*> m_images;
    std::map<std::string, UILabel*> m_labels;
    std::map<std::string, UIButton*> m_buttons;
    std::string m_currentMenu;
};

}

#endif
