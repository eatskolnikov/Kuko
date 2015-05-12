// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "MenuManager.hpp"
#include "ImageManager.hpp"
#include "FontManager.hpp"
#include "LuaManager.hpp"
#include "LanguageManager.hpp"
#include "../utilities/Logger.hpp"

#include <fstream>

namespace kuko
{

MenuManager::MenuManager()
{
    // pages start at 1, with an element visible on page 0 being visible on all pages.
    m_currentPage = 1;
    m_maxPages = 1;
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
    Logger::Out( "Page menu is now " + Logger::IntToString( m_currentPage ) );
}


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
            m_images.insert( std::pair<std::string, UIImage*>( id, image ) );
        }
        else if ( type == "button" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string textureId = LuaManager::Menu_GetElementString( index, "texture_id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string text = LanguageManager::Text( textId );
            std::string effect = LuaManager::Menu_GetElementString( index, "effect" );

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

            m_buttons.insert( std::pair<std::string, UIButton*>( id, button ) );
        }
        else if ( type == "label" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string text = LanguageManager::Text( textId );
            std::string effect = LuaManager::Menu_GetElementString( index, "effect" );
            int effectSpeed = LuaManager::Menu_GetElementInt( index, "effect_speed" );

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

            m_labels.insert( std::pair<std::string, UILabel*>( id, label ) );
        }
    }

    int uiElements = m_images.size() + m_labels.size() + m_buttons.size();
    Logger::Out( "Menu has " + Logger::IntToString( uiElements ) + " elements", "MenuManager::SetupMenu" );
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

    m_images.clear();
    m_labels.clear();
    m_buttons.clear();
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
}

void MenuManager::ResetMouse()
{
    m_mouseDown = false;
}

bool MenuManager::IsButtonClicked( const std::string& key, int mouseX, int mouseY )
{
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
            bool isHit = ( mouseX >= btn.x && mouseX <= btn.x + btn.w &&
                     mouseY >= btn.y && mouseY <= btn.y + btn.h );

            m_mouseDown = isHit;
            return isHit;
        }
    }

    m_mouseDown = false;
    return false;
}

}
