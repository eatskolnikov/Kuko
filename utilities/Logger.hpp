// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_LOGGER
#define _KUKO_LOGGER

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
    public:
    static void Setup();
    static void Cleanup();
    static void SetLogLevel( int val );

    static void Out( const std::string& message, const std::string& location = "", bool condition = true, int level = 0 );
    static void Error( const std::string& message, const std::string& location = "" );

    static double GetTimestamp();

    static std::string IntToString( int number );

    private:
    static std::ofstream m_file;
    static time_t m_startTime;
    static time_t m_lastTimestamp;
    static int m_logLevel;
};

// Shortcut expressions for logger
#define I2S( number ) Logger::IntToString( number )
#define LOG( msg ) Logger::Out( msg );
#define LOGLOC( msg, loc ) Logger::Out( msg, loc );
#define ERR( msg, loc ) Logger::Error( msg, loc );

#endif
