/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include "Platform/Window.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#elif TGON_PLATFORM_IOS
#   include "IOS/IOSInputManager.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidInputManager.h"
#endif

namespace tgon
{

class InputManager final :
    private PlatformInputManager
{
/**@section Constructor */
public:
    explicit InputManager(const Window& inputTargetWindow);

/**@section Method */
public:
    PlatformInputManager& GetPlatformDependency() noexcept;
    const PlatformInputManager& GetPlatformDependency() const noexcept;
    void Update();
};

} /* namespace tgon */
