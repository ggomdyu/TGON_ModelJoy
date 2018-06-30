/**
 * @file    Log.h
 * @author  ggomdyu
 * @since   04/01/2016
 * @brief   Set of platform agnostic Log interfaces.
 */

#pragma once
#include <cstdarg>

#include "Core/Platform/Config.h"

namespace tgon
{

enum class LogLevel;

void Log(LogLevel logLevel, const char* formatStr, ...);

void Assert(bool condition);

void Assert(bool condition, const char* formatStr, ...);

} /* namespace tgon */
