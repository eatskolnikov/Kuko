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
