/**
 * @filename    GenericWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @brief       The platform-agnostic Window class.
 */

#pragma once
#include "GenericWindowFwd.h"

#include "../Config.h"

#include "Core/Object/Object.h"
#include "Core/Object/Delegate.h"
#include "Core/Math/Extent.h"
#include "Core/Math/Point.h"

#include <boost/noncopyable.hpp>
#include <string>
#include <cstdint>

namespace tgon
{
namespace core
{

class TGON_API GenericWindow :
    public Object
{
public:
    TGON_RUNTIME_OBJECT(GenericWindow)

/* @section Public constructor */
public:
    GenericWindow() noexcept;
    GenericWindow(const GenericWindow&) = default;
    GenericWindow(GenericWindow&&) = default;

/* @section Public destructor */
public:
    virtual ~GenericWindow() = 0;

/* @section Public operator */
public:
    GenericWindow& operator=(const GenericWindow&) = default;
    GenericWindow& operator=(GenericWindow&&) = default;

/* @section Public method */
public:
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;
    virtual void Maximize() = 0;
    virtual void Minimize() = 0;
    virtual void BringToFront() {}

    virtual void SetPosition(int32_t x, int32_t y) = 0;
    virtual void SetSize(int32_t width, int32_t height) = 0;
    virtual void SetTitle(const char* title) = 0;
    virtual void SetFullScreen(bool isFullScreen) {}
    virtual void SetTopMost(bool setTopMost) = 0;
    virtual void SetTransparency(float transparency) = 0;
    //void SetTransparencyPerPixel(const core::Color4f& pixel, float opacity);
    virtual void GetPosition(int32_t* x, int32_t* y) const = 0;
    I32Point GetPosition() const;
    virtual void GetSize(int32_t* width, int32_t* height) const = 0;
    I32Extent2D GetSize() const;
    virtual void GetTitle(char* destStr) const = 0;
    virtual float GetTransparency() const = 0;
    virtual const void* GetNativeWindow() const = 0;
    void* GetNativeWindow();
    virtual bool HasCaption() const = 0;
    virtual bool IsResizable() const = 0;
    virtual bool IsMaximized() const = 0;
    virtual bool IsMinimized() const = 0;
    virtual bool IsTopMost() const = 0;
    bool IsClosed() const noexcept;

    Delegate<void(int32_t, int32_t)> OnWindowMove;
    Delegate<void(int32_t, int32_t)> OnWindowResize;
    Delegate<void()> OnWindowMaximize;
    Delegate<void()> OnWindowMinimize;
    Delegate<void()> OnWindowEnterFullScreen;
    Delegate<void()> OnWindowExitFullScreen;
    Delegate<void()> OnWindowWillClose;
    Delegate<void()> OnWindowDidClose;
    Delegate<void()> OnWindowGetFocus;
    Delegate<void()> OnWindowLoseFocus;

/* @section Protected variable */
protected:
    bool m_isClosed;
};

} /* namespace core */
} /* namespace tgon */