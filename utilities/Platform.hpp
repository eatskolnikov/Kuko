#ifndef PLATFORM_SPECIFIC_HPP
#define PLATFORM_SPECIFIC_HPP

#include <string>

enum OperatingSystem { UNKNOWN, WINDOWS32, WINDOWS64, APPLE, LINUX, UNIX, IOS, ANDROID };

class Platform
{
    public:
    static OperatingSystem GetOperatingSystem();
    static std::string GetOperatingSystemName( OperatingSystem system );
};

#endif
