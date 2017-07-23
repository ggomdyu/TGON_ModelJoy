#include "PrecompiledHeader.pch"
#include "GenericTime.h"

#include <chrono>
#include <ctime>

namespace tgon
{
namespace platform
{
namespace
{

const uint32_t g_oldOSExecutionTime = GetOSExecutionTime();

} /* namespace */

TGON_API uint32_t GetProcessExecutionTime()
{
    return GetOSExecutionTime() - g_oldOSExecutionTime;
}

TGON_API time_t GetUnixTime()
{
    return static_cast<time_t>(std::time(nullptr));
}

} /* namespace platform */
} /* namespace tgon */
