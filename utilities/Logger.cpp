#include "Logger.hpp"
#include <ctime>
#include <sstream>

std::ofstream Logger::m_file;
time_t Logger::m_startTime;

void Logger::Setup()
{
    m_file.open( "log.txt" );
    m_startTime = time( 0 );
    m_file << "Program begin at " << __DATE__ << " " << __TIME__ << std::endl << std::endl;
}

void Logger::Cleanup()
{
    m_file << std::endl << "Program end, elapsed time: " << GetTimestamp() << " second(s)" << std::endl;
    m_file.close();
}

void Logger::Out( const std::string& message, const std::string& location /* = "" */, bool condition /* = true */ )
{
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

std::string Logger::IntToString( int number )
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}


