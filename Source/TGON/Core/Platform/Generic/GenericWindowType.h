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
namespace core
{

struct WindowStyle final
{
    std::string title = u8"Hello World!";

    uint16_t x = 100;
    uint16_t y = 100;
    uint16_t width = 500;
    uint16_t height = 500;

    bool hasCaption = true;
    bool enableSystemButton = true;
    bool supportTransparency = false;
    bool supportPerPixelTransparency = false;
    bool resizeable = true;
    bool topMost = false;
    bool maximized = false;
    bool minimized = false;
    bool showMiddle = false;
    bool setFullScreen = false;
};

} /* namespace core */
} /* namespace tgon */