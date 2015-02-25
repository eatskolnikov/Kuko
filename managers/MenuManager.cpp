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

MenuManager::~MenuManager()
{
    ClearMenu();
}

void MenuManager::Reload()
{
    SetupMenu( m_currentMenu );
}

void MenuManager::SetupMenu( const std::string& path )
{
    ClearMenu();
    m_currentMenu = path;

    Logger::Out( "Load menu " + path, "MenuManager::SetupMenu" );

    LuaManager::LoadScript( path );
    int ct = LuaManager::Menu_GetElementCount();

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

            UIImage* image = new UIImage;
            image->Setup( id, pos, kuko::ImageManager::GetTexture( textureId ) );
            m_images.insert( std::pair<std::string, UIImage*>( id, image ) );
        }
        else if ( type == "button" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string textureId = LuaManager::Menu_GetElementString( index, "texture_id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string text = LanguageManager::Text( textId );

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

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

            UIButton* button = new UIButton;
            button->Setup( id, text, pos,
            kuko::ImageManager::GetTexture( textureId ),
            { 0xFF, 0xFF, 0xFF, 0xFF }, color,
            kuko::FontManager::GetFont( fontId ), pad );
            m_buttons.insert( std::pair<std::string, UIButton*>( id, button ) );
        }
        else if ( type == "label" )
        {
            std::string id = LuaManager::Menu_GetElementString( index, "id" );
            std::string fontId = LuaManager::Menu_GetElementString( index, "font_id" );
            std::string textId = LuaManager::Menu_GetElementString( index, "text_id" );
            std::string text = LanguageManager::Text( textId );

            SDL_Color color;
            color.r = LuaManager::Menu_GetElementInt( index, "font_r" );
            color.g = LuaManager::Menu_GetElementInt( index, "font_g" );
            color.b = LuaManager::Menu_GetElementInt( index, "font_b" );
            color.a = LuaManager::Menu_GetElementInt( index, "font_a" );

            SDL_Rect pos;
            pos.x = LuaManager::Menu_GetElementInt( index, "x" );
            pos.y = LuaManager::Menu_GetElementInt( index, "y" );
            pos.w = LuaManager::Menu_GetElementInt( index, "width" );
            pos.h = LuaManager::Menu_GetElementInt( index, "height" );

            UILabel* label = new UILabel;
            label->Setup( id, text,
            pos, color,
            kuko::FontManager::GetFont( fontId ) );
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

void MenuManager::Draw()
{
    for (   std::map<std::string, UIImage*>::iterator it = m_images.begin();
            it != m_images.end();
            ++it )
    {
        it->second->Draw();
    }
    for (   std::map<std::string, UIButton*>::iterator it = m_buttons.begin();
            it != m_buttons.end();
            ++it )
    {
        it->second->Draw();
    }
    for (   std::map<std::string, UILabel*>::iterator it = m_labels.begin();
            it != m_labels.end();
            ++it )
    {
        it->second->Draw();
    }
}

bool MenuManager::IsButtonClicked( const std::string& key, int mouseX, int mouseY )
{
    // TODO: Accessing a key might automatically create the object - not certain, look into.
    if ( m_buttons[ key ] == NULL )
    {
        return false;
    }

    SDL_Rect btn = m_buttons[ key ]->GetPosition();

    return ( mouseX >= btn.x && mouseX <= btn.x + btn.w &&
             mouseY >= btn.y && mouseY <= btn.y + btn.h );
}

}