#include "PlatformSpecific.hpp"

OperatingSystem PlatformSpecific::GetOperatingSystem()
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
