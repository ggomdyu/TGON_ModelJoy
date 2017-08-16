#include "PrecompiledHeader.pch"
#include "WindowsTime.h"

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{
namespace platform
{

TGON_API uint64_t GetOSExecutionTime()
{
    return GetTickCount64();
}

TGON_API DateTime GetSystemTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawUtcTime;
    gmtime_s(&rawUtcTime, &unixTime);

    return DateTime(rawUtcTime);
}

TGON_API DateTime GetLocalTime()
{
    std::time_t unixTime = std::time(nullptr);

    std::tm rawLocalTime;
    gmtime_s(&rawLocalTime, &unixTime);
    localtime_s(&rawLocalTime, &unixTime);
    
    return DateTime(rawLocalTime);
}

} /* namespace platform */
} /* namespace tgon */
