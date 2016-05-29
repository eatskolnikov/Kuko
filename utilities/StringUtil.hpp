// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_STRINGUTIL
#define _KUKO_STRINGUTIL

#include <string>
#include <chrono>
#include <ctime>

class StringUtil
{
    public:
    static std::string IntToString( int number );
    static std::string FloatToString( float number );
    static int StringToInt( const std::string& text );
    static std::string RemoveWhitespace( const std::string& text, const std::string& replaceWith = "" );
    static std::string GetTime();
};

#endif
