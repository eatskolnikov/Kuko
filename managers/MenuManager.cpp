// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "MenuManager.hpp"
#include "ImageManager.hpp"
#include "FontManager.hpp"
#include "LuaManager.hpp"
#include "LanguageManager.hpp"
#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

#include <fstream>

namespace kuko
{

MenuManager::MenuManager()
{
    // pages start at 1, with an element visible on page 0 being visible on all pages.
    m_currentPage = 1;
    m_maxPages = 1;
    m_activeTextbox = NULL;
}

MenuManager::~MenuManager()
{
    ClearMenu();
}

void MenuManager::Reload()
{
    SetupMenu( m_currentMenu );
}

int MenuManager::GetCurrentPage()
{
    return m_currentPage;
}

void MenuManager::SetCurrentPage( int val )
{
    m_currentPage = val;
    if ( m_currentPage > m_maxPages )
    {
        m_currentPage = m_maxPages;
    }
}

void MenuManager::NextPage()
{
    m_currentPage++;
    if ( m_currentPage > m_maxPages )
    {
        m_currentPage = 1;
    }
    Logger::Out( "Page menu is now " + StringUtil::IntToString( m_currentPage ) );
}

#ifdef NOLUA
void MenuManager::SetupMenu( const std::string& path )
{
    Logger::Error( "Error: Lualess Kuko does not currently support creating menus from external files.", "MenuManager::SetupMenu" );
}

#else
void MenuManager::SetupMenu( const std::string& path )
{
    Logger::Out( "Setup Menu " + path, "MenuManager::SetupMenu" );
    ClearMenu();
    m_currentMenu = path;

    LuaManager::LoadScript( path );
    int ct = LuaManager::Menu_GetElementCount();
    m_mouseDown = false;
    m_maxPages = LuaManager::Menu_GetOptionInt( "total_pages" );

    for ( int i = 0; i < ct; i++ )
    {
        int index = i+1; // account for Lua starting at 1
        std::string type = LuaManager::Menu_GetElementString( index, "ui_type" );

        if ( type == "image" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string textureId = LuaManager::Menu_GetElementString( index, "texture_id" );

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

            // Visible page is 0 = all pages, 1 = page 1 (lua), page 0 (c++)
            int page = LuaManager::Menu_GetElementInt( index, "page" );

            UIImage* image = new UIImage;
            image->Setup( id, pos, kuko::ImageManager::GetTexture( textureId ) );
            if ( page != 0 ) { image->SetVisiblePage( page ); }

            AddImage( id, image );
        }
        else if ( type == "button" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string textureId = LuaManager::Menu_GetElementString( index, "texture_id" );
            std::string languageId = LuaManager::Menu_GetElementString( index, "language_id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string effect = LuaManager::Menu_GetElementString( index, "effect" );
            std::string text;
            if ( languageId == "" )
            {
                text = LanguageManager::Text( textId );
            }
            else
            {
                text = LanguageManager::Text( languageId, textId );
            }

            bool centered = ( LuaManager::Menu_GetElementInt( index, "centered_text" ) == 1 );

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

            int page = LuaManager::Menu_GetElementInt( index, "page" );

            UIButton* button = new UIButton;
            if ( textId != "" )
            {
                SDL_Rect pad;
                pad.x = LuaManager::Menu_GetElementInt( index, "pad_x1" );
                pad.y = LuaManager::Menu_GetElementInt( index, "pad_y1" );
                pad.w = LuaManager::Menu_GetElementInt( index, "pad_x2" );
                pad.h = LuaManager::Menu_GetElementInt( index, "pad_y2" );

                SDL_Color color;
                color.r = LuaManager::Menu_GetElementInt( index, "font_r" );
                color.g = LuaManager::Menu_GetElementInt( index, "font_g" );
                color.b = LuaManager::Menu_GetElementInt( index, "font_b" );
                color.a = LuaManager::Menu_GetElementInt( index, "font_a" );

                button->Setup( id, text, pos, centered,
                    kuko::ImageManager::GetTexture( textureId ),
                    { 0xFF, 0xFF, 0xFF, 0xFF }, color,
                    kuko::FontManager::GetFont( fontId ), pad );
            }
            else
            {
                button->Setup( id, pos, centered,
                    kuko::ImageManager::GetTexture( textureId ),
                    { 0xFF, 0xFF, 0xFF, 0xFF } );
            }
            if ( effect != "" )
            {
                int speed = LuaManager::Menu_GetElementInt( index, "effect_speed" );
                std::string subTexture = LuaManager::Menu_GetElementString( index, "texture_id_2" );

                button->SetupAnimateEffect( effect, kuko::ImageManager::GetTexture( subTexture ), speed );
            }
            if ( page != 0 ) { button->SetVisiblePage( page ); }

            AddButton( id, button );
        }
        else if ( type == "label" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string effect = LuaManager::Menu_GetElementString( index, "effect" );
            int effectSpeed = LuaManager::Menu_GetElementInt( index, "effect_speed" );
            std::string languageId = LuaManager::Menu_GetElementString( index, "language_id" );
            std::string text;
            if ( languageId == "" )
            {
                text = LanguageManager::Text( textId );
            }
            else
            {
                text = LanguageManager::Text( languageId, textId );
            }

            SDL_Color color;
            color.r = LuaManager::Menu_GetElementInt( index, "font_r" );
            color.g = LuaManager::Menu_GetElementInt( index, "font_g" );
            color.b = LuaManager::Menu_GetElementInt( index, "font_b" );
            color.a = LuaManager::Menu_GetElementInt( index, "font_a" );

            int page = LuaManager::Menu_GetElementInt( index, "page" );

            bool useShadow = LuaManager::Menu_GetElementInt( index, "use_shadow" );
            SDL_Color shadowColor;
            int offsetX, offsetY;
            if ( useShadow )
            {
                shadowColor.r = LuaManager::Menu_GetElementInt( index, "shadow_r" );
                shadowColor.g = LuaManager::Menu_GetElementInt( index, "shadow_g" );
                shadowColor.b = LuaManager::Menu_GetElementInt( index, "shadow_b" );
                shadowColor.a = LuaManager::Menu_GetElementInt( index, "shadow_a" );
                offsetX = LuaManager::Menu_GetElementInt( index, "shadow_offset_x" );
                offsetY = LuaManager::Menu_GetElementInt( index, "shadow_offset_y" );
            }

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

            bool centered = ( LuaManager::Menu_GetElementInt( index, "centered_text" ) == 1 );

            UILabel* label = new UILabel;
            label->Setup( id, text,
                pos, centered, color,
                kuko::FontManager::GetFont( fontId ), effect, effectSpeed, useShadow, shadowColor, offsetX, offsetY );

            if ( page != 0 ) { label->SetVisiblePage( page ); }

            AddLabel( id, label );
        }
        else if ( type == "textbox" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string languageId = LuaManager::Menu_GetElementString( index, "language_id" );
            std::string text;
            int maxLength = LuaManager::Menu_GetElementInt( index, "max_length" );

            if ( languageId == "" )
            {
                text = LanguageManager::Text( textId );
            }
            else
            {
                text = LanguageManager::Text( languageId, textId );
            }

            SDL_Color bgColor;
            bgColor.r = LuaManager::Menu_GetElementInt( index, "background_r" );
            bgColor.g = LuaManager::Menu_GetElementInt( index, "background_g" );
            bgColor.b = LuaManager::Menu_GetElementInt( index, "background_b" );
            bgColor.a = LuaManager::Menu_GetElementInt( index, "background_a" );

            SDL_Color selectedBgColor;
            selectedBgColor.r = LuaManager::Menu_GetElementInt( index, "selected_r" );
            selectedBgColor.g = LuaManager::Menu_GetElementInt( index, "selected_g" );
            selectedBgColor.b = LuaManager::Menu_GetElementInt( index, "selected_b" );
            selectedBgColor.a = LuaManager::Menu_GetElementInt( index, "selected_a" );

            SDL_Color textColor;
            textColor.r = LuaManager::Menu_GetElementInt( index, "font_r" );
            textColor.g = LuaManager::Menu_GetElementInt( index, "font_g" );
            textColor.b = LuaManager::Menu_GetElementInt( index, "font_b" );
            textColor.a = LuaManager::Menu_GetElementInt( index, "font_a" );

            int page = LuaManager::Menu_GetElementInt( index, "page" );

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

            UITextBox* textbox = new UITextBox;
            textbox->Setup( id, pos, bgColor, selectedBgColor, textColor, kuko::FontManager::GetFont( fontId ), maxLength );

            if ( page != 0 ) { textbox->SetVisiblePage( page ); }
            m_textboxes.insert( std::pair<std::string, UITextBox*>( id, textbox ) );
        }
    }

    int uiElements = m_images.size() + m_labels.size() + m_buttons.size();
    Logger::Out( "Menu has " + StringUtil::IntToString( uiElements ) + " elements", "MenuManager::SetupMenu" );
}
#endif

void MenuManager::AddLabel( const std::string& id, UILabel* label )
{
    m_labels.insert( std::pair<std::string, UILabel*>( id, label ) );
}

void MenuManager::AddLabel( const std::string& id, const std::string& lbl, int x, int y, int width, int height, bool centered, SDL_Color textColor, TTF_Font* font )
{
    UILabel* label = new UILabel;
    SDL_Rect pos; pos.x = x; pos.y = y; pos.w = width; pos.h = height;
    label->Setup( id, lbl, pos, centered, textColor, font );
    AddLabel( id, label );
}

void MenuManager::AddButton( const std::string& id, UIButton* button )
{
    m_buttons.insert( std::pair<std::string, UIButton*>( id, button ) );
}

void MenuManager::AddButton( const std::string& id,SDL_Texture* ptrTexture,  int x, int y, int width, int height, bool centered,
    SDL_Color buttonColor )
{
    UIButton* button = new UIButton;
    SDL_Rect pos; pos.x = x; pos.y = y; pos.w = width; pos.h = height;
    button->Setup( id, pos, centered, ptrTexture, buttonColor );
    AddButton( id, button );
}

void MenuManager::AddImage( const std::string& id, UIImage* image )
{
    m_images.insert( std::pair<std::string, UIImage*>( id, image ) );
}

void MenuManager::AddImage( const std::string& id, SDL_Texture* ptrTexture, int x, int y, int width, int height, bool centered,
    const std::string& effectName, int effectMax )
{
    UIImage* image = new UIImage;
    SDL_Rect pos; pos.x = x; pos.y = y; pos.w = width; pos.h = height;
    pos.x = kuko::Application::GetDefaultWidth() / 2 - width / 2;
    image->Setup( id, pos, ptrTexture );
    if ( effectName != "" )
    {
        image->SetEffect( effectName, effectMax );
    }
    AddImage( id, image );
}

void MenuManager::ClearMenu()
{
    for (   std::map<std::string, UIImage*>::iterator it = m_images.begin();
            it != m_images.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            delete it->second;
            it->second = NULL;
        }
    }
    for (   std::map<std::string, UIButton*>::iterator it = m_buttons.begin();
            it != m_buttons.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            delete it->second;
            it->second = NULL;
        }
    }
    for (   std::map<std::string, UILabel*>::iterator it = m_labels.begin();
            it != m_labels.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            delete it->second;
            it->second = NULL;
        }
    }
    for (   std::map<std::string, UITextBox*>::iterator it = m_textboxes.begin();
            it != m_textboxes.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            delete it->second;
            it->second = NULL;
        }
    }

    m_images.clear();
    m_labels.clear();
    m_buttons.clear();
    m_textboxes.clear();
}

void MenuManager::Update()
{
    for (   std::map<std::string, UILabel*>::iterator it = m_labels.begin();
            it != m_labels.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            it->second->Update();
        }
    }
    for (   std::map<std::string, UIButton*>::iterator it = m_buttons.begin();
            it != m_buttons.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            it->second->Update();
        }
    }
    for (   std::map<std::string, UIImage*>::iterator it = m_images.begin();
            it != m_images.end();
            ++it )
    {
        if ( it->second != NULL )
        {
            it->second->Update();
        }
    }
}

void MenuManager::Draw()
{
    for (   std::map<std::string, UIImage*>::iterator it = m_images.begin();
            it != m_images.end();
            ++it )
    {
        if ( it->second->GetVisiblePage() == m_currentPage || it->second->GetVisiblePage() == 0 )
        {
            it->second->Draw();
        }
    }
    for (   std::map<std::string, UIButton*>::iterator it = m_buttons.begin();
            it != m_buttons.end();
            ++it )
    {
        if ( it->second->GetVisiblePage() == m_currentPage || it->second->GetVisiblePage() == 0 )
        {
            it->second->Draw();
        }
    }
    for (   std::map<std::string, UILabel*>::iterator it = m_labels.begin();
            it != m_labels.end();
            ++it )
    {
        if ( it->second->GetVisiblePage() == m_currentPage || it->second->GetVisiblePage() == 0 )
        {
            it->second->Draw();
        }
    }
    for (   std::map<std::string, UITextBox*>::iterator it = m_textboxes.begin();
            it != m_textboxes.end();
            ++it )
    {
        if ( it->second->GetVisiblePage() == m_currentPage || it->second->GetVisiblePage() == 0 )
        {
            it->second->Draw();
        }
    }
}

void MenuManager::ResetMouse()
{
    m_mouseDown = false;
}

bool MenuManager::IsButtonClicked( const std::string& key, float mouseX, float mouseY )
{
    float adjX = mouseX / kuko::Application::GetWidthRatio();
    float adjY = mouseY / kuko::Application::GetHeightRatio();

    if ( m_mouseDown )
    {
        return false;
    }
    for ( std::map< std::string, UIButton* >::iterator iter = m_buttons.begin();
            iter != m_buttons.end(); ++iter )
    {
        if ( iter->second->GetId() == key )
        {
            SDL_Rect btn = iter->second->GetPosition();

            bool isHit = ( adjX >= btn.x && adjX <= btn.x + btn.w &&
                     adjY >= btn.y && adjY <= btn.y + btn.h );

            m_mouseDown = isHit;
            return isHit;
        }
    }

    m_mouseDown = false;
    return false;
}

void MenuManager::CheckTextboxClick( float mouseX, float mouseY )
{
    // If a textbox is clicked, make sure the widget visually represents that.
    for ( std::map< std::string, UITextBox* >::iterator iter = m_textboxes.begin();
            iter != m_textboxes.end(); ++iter )
    {
        SDL_Rect widget = iter->second->GetPosition();
        bool isHit = ( mouseX >= widget.x && mouseX <= widget.x + widget.w &&
                 mouseY >= widget.y && mouseY <= widget.y + widget.h );

        if ( isHit )
        {
            if ( m_activeTextbox != NULL )
            {
                m_activeTextbox->SetActive( false );
            }
            Logger::Out( "Set active text box to " + iter->second->GetId(), "MenuManager::CheckTextboxClick" );
            m_activeTextbox = iter->second;
            m_activeTextbox->SetActive( true );
        }
    }
}

std::string MenuManager::GetTextboxValue( const std::string& key )
{
    for ( std::map< std::string, UITextBox* >::iterator iter = m_textboxes.begin();
            iter != m_textboxes.end(); ++iter )
    {
        if ( iter->second->GetId() == key )
        {
            return iter->second->GetText();
        }
    }
    return "";
}

void MenuManager::SetTextEditing( bool turnOn )
{
    if ( turnOn )
    {
        SDL_StartTextInput();
    }
    else
    {
        SDL_StopTextInput();
    }
}

void MenuManager::AppendToActiveTextBox( const std::string& text )
{
    Logger::Out( "Append \"" + text + "\" to active text box.", "MenuManager::AppendToActiveTextBox" );
    if ( m_activeTextbox == NULL )
    {
        return;
    }

    m_activeTextbox->AppendText( text );
}

void MenuManager::RemoveLastCharacterOfActiveTextBox()
{
    if ( m_activeTextbox == NULL )
    {
        return;
    }

    m_activeTextbox->RemoveLastLetter();
}

void MenuManager::UpdateLabelText( const std::string& id, const std::string& text )
{
    m_labels[ id ]->ChangeText( text );
}

}
