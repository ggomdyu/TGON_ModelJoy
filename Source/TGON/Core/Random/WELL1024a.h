/**
 * @filename    WELL1024a.h
 * @author      ggomdyu
 * @since       05/05/2017
 * @brief       Random number generate algorithm
 * @see         http://www.iro.umontreal.ca/~panneton/WELLRNG.html
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{
namespace core
{

TGON_API void SrandWELL1024a();

/* @brief	Get random value between 0.0 ~ 1.0 */
TGON_API double WELL1024a();

} /* namespace core */
} /* namespace tgon */
