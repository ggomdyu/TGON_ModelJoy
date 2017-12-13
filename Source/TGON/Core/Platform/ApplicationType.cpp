/**
 * @filename    ApplicationType.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include <boost/predef/os.h>
#include <cstdint>

namespace tgon 
{
namespace platform
{

struct AppMessage
{
    void* rawMsg;
    void* param1;
    void* param2;
};

enum class MessageBoxIconType
{
    Informational = 0,
    Warning = 1,
};

struct BatteryState
{
/* @section Public constructor */
public:
	constexpr BatteryState(bool hasBattery, bool isCharging, int16_t batteryLifePercent) noexcept;

/* @section	Public variable */
public:
    /* @brief   Records whether the current device has baterry. */
	const bool hasBattery;

    /* @brief   Records whether the baterry is charging. */
    const bool isCharging;

    /* @brief   Records the battery percentage between 0 and 100. or -1 if status is unknown. */
	const int16_t batteryPercentage;
};

constexpr BatteryState::BatteryState(bool hasBattery, bool isCharging, int16_t batteryPercentage) noexcept :
	hasBattery(hasBattery),
    isCharging(isCharging),
    batteryPercentage(hasBattery ? batteryPercentage : -1)
{
}

} /* namespace platform */
} /* namespace tgon */