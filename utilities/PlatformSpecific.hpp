#ifndef PLATFORM_SPECIFIC_HPP
#define PLATFORM_SPECIFIC_HPP

enum OperatingSystem { UNKNOWN, WINDOWS32, WINDOWS64, APPLE, LINUX, UNIX, IOS, ANDROID };

class PlatformSpecific
{
    public:
    static OperatingSystem GetOperatingSystem();
};

#endif
