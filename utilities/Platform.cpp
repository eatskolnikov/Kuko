#include "Platform.hpp"

OperatingSystem Platform::GetOperatingSystem()
{

#ifdef _WIN32
    #ifdef _WIN64
        return WINDOWS64;

    #else
        return WINDOWS32;

    #endif

#elif __APPLE__

    #ifdef TARGET_OS_MAC
        return APPLE;

    #else
        return UNKNOWN;

    #endif

#elif __linux__
    return LINUX;

#elif __unix__
    return UNIX;

#else
    return UNKNOWN;

#endif

}

std::string Platform::GetOperatingSystemName( OperatingSystem system )
{
    if      ( system == WINDOWS32 ) { return "WINDOWS32"; }
    else if ( system == WINDOWS64 ) { return "WINDOWS64"; }
    else if ( system == LINUX )     { return "LINUX"; }
    else if ( system == UNIX )      { return "UNIX"; }
    else if ( system == APPLE )     { return "APPLE"; }
    else if ( system == ANDROID )   { return "ANDROID"; }
    return "UNKNOWN";
}
