/**
 * @filename    Application.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include <boost/predef/os.h>
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>
#if BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <Windows.h>
#endif

#include "Config.h"

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    namespace platform\
    {\
    std::shared_ptr<class Application> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, class Application*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from Application.");\
        return std::make_shared<className>();\
    }\
    } /* namespace platform */\
    } /* namespace tgon */

#if BOOST_OS_MACOS
@class NSEvent;
#endif

namespace tgon
{
namespace platform
{

class TGON_API Application :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Application() = default;
    explicit Application(const struct WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~Application() = default;

/* @section Public method */
public:
    void Initialize(const struct WindowStyle& windowStyle);

    void MessageLoop();
    void Terminate();
    void ShowMessageBox(const char* message) const;
    void ShowMessageBox(const char* message, enum class MessageBoxIconType iconType) const;
    void ShowMessageBox(const char* title, const char* message) const;
    void ShowMessageBox(const char* title, const char* message, enum class MessageBoxIconType iconType) const;

#if BOOST_OS_WINDOWS
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);
#elif BOOST_OS_MACOS
    void OnHandleMessage(NSEvent* message);
#endif
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<class Window>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<class Window>&) {}
    virtual void OnUpdate() {}

    const struct BatteryState GetBatteryState() const;
    const std::shared_ptr<class Window>& GetMainWindow() const noexcept;

protected:
    std::shared_ptr<class Window> m_mainWindow;
};

} /* namespace platform */
} /* namespace tgon */
