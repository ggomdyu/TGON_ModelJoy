/**
 * @file    Gamepad.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif
#include "InputManager.h"

namespace tgon
{
    
class TGON_API Gamepad final
{
/* @section Public constructor */
public:
    explicit Gamepad(InputManager& inputManager);
    
/* @section Public destructor */
public:
    ~Gamepad();
    
/* @section Public method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const PlatformGamepad& GetImpl() const noexcept;
    PlatformGamepad& GetImpl() noexcept;
    
/* @section Private variable */
private:
    PlatformGamepad m_platformGamepad;
};
    
} /* namespace tgon */
