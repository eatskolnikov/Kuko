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

std::string StringUtil::PointerToString( uintptr_t address )
{
    std::stringstream ss;
    ss << address;
    return ss.str();
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

std::string StringUtil::GetTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t( now );
    return ctime( &time );
}
