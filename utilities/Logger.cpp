// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Logger.hpp"
#include <iomanip>

std::ofstream Logger::m_file;
time_t Logger::m_startTime;
time_t Logger::m_lastTimestamp;
int Logger::m_logLevel;
std::string Logger::m_categoryFilter;
int Logger::m_rowCount;

/*
    m_logLevel:
    * 0: Mundane
*/

void Logger::Setup()
{
    m_rowCount = 0;
    m_logLevel = 0;
    m_file.open( "log.html" );
    m_startTime = GetTimestamp();
    m_lastTimestamp = m_startTime;

    m_file << "<html><head><title>LOG " << __DATE__ << "</title></head><body>" << std::endl;
    m_file << "<style>" << std::endl;
    m_file << "table { font-family: sans-serif; width: 100%; }" << std::endl;
    m_file << "tr.highlight { background: #FFFF00; } " << std::endl;
    m_file << "td { border-bottom: solid 1px #CCCCCC; } " << std::endl;
    m_file << "table .time { padding-right: 25px; }" << std::endl;
    m_file << "table .location { padding-right: 25px; }" << std::endl;
    m_file << "table td.time { font-size: 14px; }" << std::endl;
    m_file << "table td.location { font-size: 14px; }" << std::endl;
    m_file << "table td.message { font-size: 14px; }" << std::endl;
    m_file << "table .odd { background: #DDDDDD; }" << std::endl;
    m_file << "table .error { background: #FFA5A5; }" << std::endl;
    m_file << "table .debug { background: #C3A5FF; }" << std::endl;
    m_file << "</style>" << std::endl;
    m_file << "<table>" << std::endl;
    m_file << "<tr>"
        << "<td class='time'><strong>TIME</strong></td>"
        << "<td class='location'><strong>LOCATION</strong></td>"
        << "<td class='message'><strong>MESSAGE</strong></td>"
        << "</tr>" << std::endl;
    Out( "Logging Begins", "Logger::Setup" );
}

void Logger::Setup( int logLevel, const std::string& filter )
{
    Setup();
    SetLogLevel( logLevel );
    SetFilterWord( filter );
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
    Out( "Logging Ends", "Logger::Cleanup" );
    m_file << "</table>" << std::endl;
    m_file << "</body></html>" << std::endl;
    m_file.close();
}

void Logger::OutHighlight( const std::string& message, const std::string& location )
{
    std::cout << GetFormattedTimestamp();
    if ( location != "" ) { std::cout << " @ " << location; }
    std::cout << std::endl << "  " << message << std::endl << std::endl;

    std::string loc = location;
    if ( loc == "" ) { loc = "-"; }

    m_file << "<tr class='highlight'>"
        << "<td class='time'>" << GetFormattedTimestamp() << "</td>"
        << "<td class='location'>" << loc << "</td>"
        << "<td class='message'>" << message << "</td>"
        << "</tr>" << std::endl;

    m_rowCount++;
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

    if ( condition )
    {
        std::cout << GetFormattedTimestamp();
        if ( location != "" ) { std::cout << " @ " << location; }
        std::cout << std::endl << "  " << message << std::endl << std::endl;

        std::string loc = location;
        if ( loc == "" ) { loc = "-"; }

        std::string rowClass = ( m_rowCount % 2 == 0 ) ? "" : "odd";

        m_file << "<tr class='" + rowClass + "'>"
            << "<td class='time'>" << GetFormattedTimestamp() << "</td>"
            << "<td class='location'>" << loc << "</td>"
            << "<td class='message'>" << message << "</td>"
            << "</tr>" << std::endl;

        m_rowCount++;
    }
}

void Logger::Error( const std::string& message, const std::string& location /* = "" */ )
{
    std::cerr   << "** " << GetTimestamp() << "\t" << message;
    if ( location != "" ) { std::cerr << " @ " << location; }
    std::cerr << std::endl;

    std::string loc = location;
    if ( loc == "" ) { loc = "-"; }

    m_file << "<tr class='error'>"
        << "<td class='time'>" << GetFormattedTimestamp() << "</td>"
        << "<td class='location'>" << loc << "</td>"
        << "<td class='message'>" << message << "</td>"
        << "</tr>" << std::endl;
}

void Logger::Debug( const std::string& message, const std::string& location )
{
    std::cerr   << "** " << GetTimestamp() << "\t" << message;
    if ( location != "" ) { std::cerr << " @ " << location; }
    std::cerr << std::endl;

    std::string loc = location;
    if ( loc == "" ) { loc = "-"; }

    m_file << "<tr class='debug'>"
        << "<td class='time'>" << GetFormattedTimestamp() << "</td>"
        << "<td class='location'>" << loc << "</td>"
        << "<td class='message'>" << message << "</td>"
        << "</tr>" << std::endl;
}

std::string Logger::GetFormattedTimestamp()
{
    time_t timestamp = GetTimestamp();
    struct tm* timeinfo;
    char buffer[80];
    time( &timestamp );
    timeinfo = localtime ( &timestamp );
    // http://www.cplusplus.com/reference/ctime/strftime/
    strftime( buffer, 80, "%H:%M:%S", timeinfo );

    std::string str( buffer );
    return str;
}

double Logger::GetTimestamp()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t( now );
}

