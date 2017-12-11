/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#elif BOOST_OS_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
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
