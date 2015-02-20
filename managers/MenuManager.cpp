// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "MenuManager.hpp"
#include "ImageManager.hpp"
#include "FontManager.hpp"
#include "../utilities/Logger.hpp"

#include <fstream>

namespace kuko
{

MenuManager::~MenuManager()
{
    ClearMenu();
}

void MenuManager::SetupMenu( const std::string& path )
{
    ClearMenu();

    std::ifstream infile;
    infile.open( path.c_str() );
    std::string buffer;

    SDL_Rect pos;
    int r, g, b, a;
    SDL_Rect pad;
    std::string text;
    std::string id;
    std::string fontId;
    std::string textureId;
    std::string type;

    while ( infile >> buffer )
    {
        // Find out what kind of UI element we're loading
        if ( buffer == "IMAGE_BEGIN" )
        {
            type = "image";
        }
        else if ( buffer == "BUTTON_BEGIN" )
        {
            type = "button";
        }
        else if ( buffer == "LABEL_BEGIN" )
        {
            type = "label";
        }


        // Load properties
        if      ( buffer == "ID" )          { infile >> id; }

        else if ( buffer == "POSX" )        { infile >> pos.x; }
        else if ( buffer == "POSY" )        { infile >> pos.y; }
        else if ( buffer == "WIDTH" )       { infile >> pos.w; }
        else if ( buffer == "HEIGHT" )      { infile >> pos.h; }

        else if ( buffer == "FONT_R" )      { infile >> r; }
        else if ( buffer == "FONT_G" )      { infile >> g; }
        else if ( buffer == "FONT_B" )      { infile >> b; }
        else if ( buffer == "FONT_A" )      { infile >> a; }

        else if ( buffer == "PADDING_X1" )  { infile >> pad.x; }
        else if ( buffer == "PADDING_X2" )  { infile >> pad.w; }
        else if ( buffer == "PADDING_Y1" )  { infile >> pad.y; }
        else if ( buffer == "PADDING_Y2" )  { infile >> pad.h; }

        else if ( buffer == "TEXTURE_ID" )  { infile >> textureId; }
        else if ( buffer == "FONT_ID" )     { infile >> fontId; }

        else if ( buffer == "TEXT_BEGIN" )
        {
            text = "";
            // Stream in
            do
            {
                if ( text != "" ) { text += " "; }
                infile >> buffer;
                if ( buffer != "TEXT_END" ) { text += buffer; }
            } while ( buffer != "TEXT_END" );
        }


        // Push new UI elementt to list
        if ( buffer == "IMAGE_END" )
        {
            UIImage* image = new UIImage;
            image->Setup( id, pos, kuko::ImageManager::GetTexture( textureId ) );
            m_images.insert( std::pair<std::string, UIImage*>( id, image ) );
        }
        else if ( buffer == "BUTTON_END" )
        {
            SDL_Color color = { r, g, b, a };
            UIButton* button = new UIButton;
            button->Setup( id, text, pos,
                kuko::ImageManager::GetTexture( textureId ),
                { 0xFF, 0xFF, 0xFF, 0xFF }, color,
                kuko::FontManager::GetFont( fontId ), pad );
            m_buttons.insert( std::pair<std::string, UIButton*>( id, button ) );
        }
        else if ( buffer == "LABEL_END" )
        {
            SDL_Color color = { r, g, b, a };
            UILabel* label = new UILabel;
            label->Setup( id, text,
                pos, color,
                kuko::FontManager::GetFont( fontId ) );
            m_labels.insert( std::pair<std::string, UILabel*>( id, label ) );
        }
    }

    infile.close();

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

}
