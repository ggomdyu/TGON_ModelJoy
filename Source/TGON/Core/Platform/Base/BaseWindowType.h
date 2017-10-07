/**
 * @filename    BaseWindowType.h
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

struct WindowStyle final
{
/* @section Public variable */
public:
    std::string caption = u8"Hello World!";

    std::size_t x = 100;
    std::size_t y = 100;
    std::size_t width = 500;
    std::size_t height = 500;

    uint32_t backgroundColor;

    bool borderless = false;
    bool enableSystemButton = true;
    bool enableFullScreenButton = false; // reserved
    bool supportWindowTransparency = false; // reserved
    bool supportPerPixelTransparency = false; // reserved
    bool resizeable = true;
    bool topMost = false;
    bool maximized = false;
    bool minimized = false;
    bool showMiddle = false;
    bool setFullScreen = false;
};

} /* namespace platform */
} /* namespace tgon */
