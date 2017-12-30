/**
 * @filename    OpenGLContextFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once
#include <boost/predef/os.h>

#ifdef BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#endif

#if BOOST_OS_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#endif

namespace tgon
{
namespace platform
{

class Window;

} /* namespace platform */

namespace rhi
{

struct VideoMode;

} /* namespace rhi */
} /* namespace tgon */