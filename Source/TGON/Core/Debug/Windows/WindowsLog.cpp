#include "PrecompiledHeader.pch"

#include <Windows.h>
#include <cstdarg>
#include <mutex>
#include <iostream>

#include "Core/String/Encoding.h"
#include "Core/String/StringTraits.h"
#include "Core/Utility/Algorithm.h"

#include "../Log.h"

namespace tgon
{
namespace
{

constexpr std::size_t g_strBufferSize = 1024 * 8;
std::unique_ptr<char[]> g_utf8StrBuffer(new char[1024 * 8] {});
std::unique_ptr<wchar_t[]> g_utf16StrBuffer(new wchar_t[1024 * 8] {});
std::mutex g_mutex;

} /* namespace detail */

void Log(LogLevel logLevel, const char* formatStr, ...)
{
#if defined(_DEBUG) || ! defined(NDEBUG)
    std::lock_guard<std::mutex> lockGuard(g_mutex);
    {   
        va_list vaList;
        va_start(vaList, formatStr);
        int utf8StrBytes = vsprintf_s(g_utf8StrBuffer.get(), g_strBufferSize, formatStr, vaList);

        bool isConvertSucceed = UTF8::Convert<UTF16LE>(g_utf8StrBuffer.get(), utf8StrBytes, reinterpret_cast<char*>(&g_utf16StrBuffer[0]), g_strBufferSize);
        if (isConvertSucceed)
        {
            if (logLevel == LogLevel::Debug)
            {
                OutputDebugStringW(g_utf16StrBuffer.get());
            }
            else if (logLevel == LogLevel::Warning)
            {
                MessageBoxW(nullptr, g_utf16StrBuffer.get(), L"", MB_OK);
            }
        }
    }
#endif
}

void Assert(bool condition)
{
#if defined(_DEBUG) || ! defined(NDEBUG)
    if (condition == false)
    {
        auto clickedBtnType = MessageBox(nullptr, L"Assertion Failed!", L"", MB_ICONHAND | MB_ABORTRETRYIGNORE);
        if (clickedBtnType == IDABORT)
        {
            std::abort();
        }
    }
#endif
}

void Assert(bool condition, const char* formatStr, ...)
{
#if defined(_DEBUG) || ! defined(NDEBUG)
    std::lock_guard<std::mutex> lockGuard(g_mutex);
    {
        if (condition == false)
        {
            if (StringTraits<char>::IsNullOrEmpty(formatStr) == true)
            {
                Assert(condition);
                return;
            }
            
            va_list vaList;
            va_start(vaList, formatStr);
            int utf8StrBytes = vsprintf_s(g_utf8StrBuffer.get(), g_strBufferSize, formatStr, vaList);

            bool isConvertSucceed = UTF8::Convert<UTF16LE>(g_utf8StrBuffer.get(), utf8StrBytes, reinterpret_cast<char*>(&g_utf16StrBuffer[0]), g_strBufferSize);
            if (isConvertSucceed)
            {
                const wchar_t(assertTitleMessage)[19] = L"Assertion Failed: ";
                auto assertTitleMessageLen = GetArraySize(assertTitleMessage) - 1;

                std::memmove(&g_utf16StrBuffer[assertTitleMessageLen], &g_utf16StrBuffer[0], sizeof(char16_t) * utf8StrBytes);
                std::memcpy(&g_utf16StrBuffer[0], assertTitleMessage, sizeof(char16_t) * assertTitleMessageLen);

                auto clickedBtnType = MessageBox(nullptr, g_utf16StrBuffer.get(), L"", MB_ICONHAND | MB_ABORTRETRYIGNORE);
                if (clickedBtnType == IDABORT)
                {
                    std::exit(3);
                }
            }
        }
    }
#endif
}

} /* namespace tgon */