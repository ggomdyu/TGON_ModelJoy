/**
 * @filename    Time.h
 * @author      ggomdyu
 * @since       05/15/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsTime.h"
#elif BOOST_OS_MACOS
#	import "MacOS/MacOSTime.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidTime.h"
#elif BOOST_OS_IOS
#	import "IOS/IOSTime.h"
#endif