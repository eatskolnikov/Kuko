#ifndef _LOGGER
#define _LOGGER

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
    public:
    static void Setup();
    static void Cleanup();

    static void Out( const std::string& message, const std::string& location = "", bool condition = true );
    static void Error( const std::string& message, const std::string& location = "" );

    static double GetTimestamp();

    static std::string IntToString( int number );

    private:
    static std::ofstream m_file;
    static time_t m_startTime;
};

#endif
