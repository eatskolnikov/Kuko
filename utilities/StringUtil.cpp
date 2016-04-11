#include "StringUtil.hpp"

#include <sstream>

std::string StringUtil::IntToString( int number )
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::string StringUtil::FloatToString( float number )
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

int StringUtil::StringToInt( const std::string& text )
{
    std::istringstream buffer( text );
    int num;
    buffer >> num;
    return num;
}

std::string StringUtil::RemoveWhitespace( const std::string& text, const std::string& replaceWith )
{
    std::string stripped = "";
    for ( int i = 0; i < text.size(); i++ )
    {
        if ( text[i] == ' ' )
        {
            stripped += replaceWith;
        }
        else
        {
            stripped += text[i];
        }
    }
    return stripped;
}
