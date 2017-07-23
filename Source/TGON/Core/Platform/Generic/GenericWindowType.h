/**
 * @filename    GenericWindowType.h
 * @author      ggomdyu
 * @since       05/05/2017
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{
namespace platform
{

struct WindowStyle
{
public:
	std::string caption = u8"Hello World!";

	std::size_t x = 100;
	std::size_t y = 100;
	std::size_t width = 500;
	std::size_t height = 500;

    bool borderless = false;
    bool enableSystemButton = true;
	bool enableFullScreen = false;
	bool supportWindowTransparency = false;
	bool supportPerPixelTransparency = false;
	bool resizeable = true;
    bool topMost = false;
    bool maximized = false;
	bool minimized = false;
    bool showMiddle = false;
    bool setFocusOnCreated = true;
};

} /* namespace platform */
} /* namespace tgon */
