// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_STRINGUTIL
#define _KUKO_STRINGUTIL

#include <string>

class StringUtil
{
    public:
    static std::string IntToString( int number );
    static int StringToInt( const std::string& text );
};

#endif
