#include "PrecompiledHeader.h"

#include "TimeZoneInfo.h"
#include "DateTime.h"

namespace tgon
{

DateTime DateTime::ToLocalTime() const
{
    return TimeZoneInfo::ConvertTimeFromUtc(*this, TimeZoneInfo::Local());
}

DateTime DateTime::ToUniversalTime() const
{
    return TimeZoneInfo::ConvertTimeToUtc(*this);
}

} /* namespace tgon */
