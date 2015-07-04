#include "LualessLanguage.hpp"

#ifdef NOLUA

#include "../../utilities/Logger.hpp"

#include <fstream>

namespace kuko
{

LualessLanguage::LualessLanguage()
{
}

bool LualessLanguage::AddLanguage( const std::string& id, const std::string& path )
{
    m_currentLanguage = id;
    return LoadLanguageFile( path );
}

std::string LualessLanguage::CurrentLanguage()
{
    return m_currentLanguage;
}

std::string LualessLanguage::Text( const std::string& key )
{
    std::string value = m_gameText[ key ];
    return ( value == "" ) ? key + " NOT FOUND" : value;
}

std::string LualessLanguage::Text( const std::string& langType, const std::string& key )
{
    Logger::Error( "Not implemented", "LualessLanguage::Text( const std::string& langType, const std::string& key )" );
//    std::string value = kuko::LuaManager::Language_GetText( langType, key );
//    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
    return "NOTIMPLEMENTED";
}

std::string LualessLanguage::GetSuggestedFont()
{
    std::string suggested = m_gameText[ "suggested_font" ];
    Logger::Out( "Suggested font: " + suggested );
    return suggested;
}

std::string LualessLanguage::SpecialField( const std::string& langType, const std::string& field, const std::string& key )
{
    Logger::Error( "Not implemented", "LualessLanguage::SpecialField( const std::string& langType, const std::string& field, const std::string& key )" );
//    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
//    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
    return "NOTIMPLEMENTED";
}

std::string LualessLanguage::SpecialField( const std::string& langType, const std::string& field, int key )
{
    Logger::Error( "Not implemented", "LualessLanguage::SpecialField( const std::string& langType, const std::string& field, int key )" );
//    std::string value = kuko::LuaManager::Language_GetSpecialField( langType, field, key );
//    return ( value == "NOTFOUND" ) ? key + " NOT FOUND" : value;
    return "NOTIMPLEMENTED";
}

int LualessLanguage::SpecialFieldCount( const std::string& langType, const std::string& field )
{
    Logger::Error( "Not implemented", "LualessLanguage::SpecialFieldCount( const std::string& langType, const std::string& field )" );
//    int value = kuko::LuaManager::Language_GetSpecialFieldCount( langType, field );
//    return value;
    return 0;
}

bool LualessLanguage::LoadLanguageFile( const std::string& path )
{
    m_gameText.clear();
    std::ifstream infile( path.c_str() );
    if ( !infile.good() )
    {
        return false;
    }

    std::string key;
    std::string delim;
    std::string value;
    std::string buffer;

    Logger::Out( "Load game text from \"" + path + "\"", "LualessLanguage::LoadLanguageFile" );
    while ( infile >> key )
    {
        infile >> delim;
        // Line ends with a pipe '|'
        value = "";
        while ( infile >> buffer && buffer != "|" )
        {
            if ( value != "" ) { value += " "; }
            value += buffer;
        }

        Logger::Out( "KEY: " + key + ", VALUE: " + value, "LualessLanguage::LoadLanguageFile" );
        m_gameText[ key ] = value;
    }

    return true;
}

}

#endif
