/**
 * @filename    WindowsMouse.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <memory>

#include "Core/Platform/Config.h"

namespace OIS
{

class Mouse;
class MouseState;

} /* namespace OIS */

namespace tgon
{

class InputManagerImpl;
enum class MouseCode;

class TGON_API MouseImpl final
{
/* @section Public constructor */
public:
    explicit MouseImpl(InputManagerImpl& platformInputManager) noexcept;

/* @section Public method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const OIS::Mouse* GetMousedDevice() const;
    OIS::Mouse* GetMouseDevice();

/* @section Private variable */
private:
    OIS::Mouse* m_mouseDevice;
    std::shared_ptr<OIS::MouseState> m_prevMouseState;
};

using PlatformMouse = MouseImpl;

} /* namespace tgon */
