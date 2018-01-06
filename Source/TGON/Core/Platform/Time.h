/**
 * @filename    Time.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Time interfaces.
 */

#pragma once
#include "Config.h"

#include <cstdint>

namespace tgon
{
namespace core
{

TGON_API int64_t GetTickCount();

/* @return  The DateTime in UTC time */
TGON_API struct DateTime GetSystemTime();

/* @return  The DateTime in Local time */
TGON_API struct DateTime GetLocalTime();

} /* namespace core */
} /* namespace tgon */
