// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Logger.hpp"
#include <ctime>

std::ofstream Logger::m_file;
time_t Logger::m_startTime;
time_t Logger::m_lastTimestamp;
int Logger::m_logLevel;
std::string Logger::m_categoryFilter;

/*
    m_logLevel:
    * 0: Mundane
*/

void Logger::Setup()
{
    m_logLevel = 0;
    m_file.open( "log.txt" );
    m_startTime = time( 0 );
    m_lastTimestamp = m_startTime;
    m_file << "Program begin at " << __DATE__ << " " << __TIME__ << std::endl << std::endl;
}

void Logger::SetLogLevel( int val )
{
    m_logLevel = val;
}

void Logger::SetFilterWord( const std::string& filter )
{
    Out( "Setting filter to only display messages of category \"" + filter + "\"" );
    m_categoryFilter = filter;
}

void Logger::Cleanup()
{
    m_file << std::endl << "Program end, elapsed time: " << GetTimestamp() << " second(s)" << std::endl;
    m_file.close();
}

void Logger::Out( const std::string& message, const std::string& location /* = "" */, const std::string& category /* = "" */, bool condition /* = true */, int level /* = 0 */ )
{
    if ( m_categoryFilter.size() > 0 )
    {
        // Filter is active

        if ( category.size() == 0
            || m_categoryFilter.find( category ) == std::string::npos )
        {
            return;
        }
    }

    if ( level < m_logLevel )
    {
        return;
    }

    time_t timestamp = GetTimestamp();
    if ( m_lastTimestamp != timestamp )
    {
        std::cout << std::endl;
        m_file << std::endl;
        m_lastTimestamp = timestamp;
    }

    if ( condition )
    {
        std::cout   << GetTimestamp() << "\t" << message;
        if ( location != "" ) { std::cout << " @ " << location; }
        std::cout << std::endl;

        m_file      << GetTimestamp() << "\t" << message;
        if ( location != "" ) { m_file << " @ " << location; }
        m_file << std::endl;
    }
}

void Logger::Error( const std::string& message, const std::string& location /* = "" */ )
{
    std::cerr   << "** " << GetTimestamp() << "\t" << message;
    if ( location != "" ) { std::cerr << " @ " << location; }
    std::cerr << "\t LINE " << __LINE__ << " FILE " << __FILE__ ;
    std::cerr << std::endl;

    m_file      << "** " << GetTimestamp() << "\t" << message;
    if ( location != "" ) { m_file << " @ " << location; }
    m_file << "\t LINE " << __LINE__ << " FILE " << __FILE__ ;
    m_file << std::endl;
}

double Logger::GetTimestamp()
{
    time_t now = time( 0 );
    double appTime = difftime( now, m_startTime );
    return appTime;
}


