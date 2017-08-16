/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <memory>
#include <type_traits>
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsWindow.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidWindow.h"
#elif BOOST_OS_MACOS
#	include "MacOS/MacOSWindow.h"
#elif BOOST_OS_IOS
#	import "IOS/IOSWindow.h"
#endif

namespace tgon
{
namespace platform
{

using SharedWindow = std::shared_ptr<platform::Window>;

template <typename _WindowType, typename... _ArgTypes, typename = typename std::enable_if<std::is_convertible<_WindowType*, Window*>::value>::type>
inline SharedWindow MakeWindow(_ArgTypes&&... args)
{
    return std::make_shared<_WindowType>(std::forward<_ArgTypes>(args)...);
}

} /* namespace platform */
} /* namespace tgon */