/**
 * @filename    WindowsWindowUtility.h
 * @author      ggomdyu
 * @since       11/12/2015
 */

#pragma once
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <windows.h>

namespace tgon
{
namespace platform
{

struct WindowStyle;

namespace windows
{

/**
 * @brief                       Create window via given arguments.
 * @param [in] windowStyle		The Style information
 * @param [in] className		The class-name which registered via RegisterClass
 * @param [in] instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param [in] extraParam		Extra data for window
 */
HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className = L"TGON", void* extraParam = nullptr);

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */
