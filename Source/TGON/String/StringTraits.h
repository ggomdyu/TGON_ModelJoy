/**
 * @file    StringTraits.h
 * @author  ggomdyu
 * @date    08/06/2017
 */

#pragma once
#include <algorithm>
#include <cstdarg>
#include <cassert>
#include <cctype>
#include <string_view>
#include <memory>

namespace tgon
{

template <typename _CharType>
class BasicStringTraits
{
/**@section Type */
public:
    using ValueType = _CharType;

/**@section Method */
public:
    static void Append(const _CharType* srcStr, int32_t srcStrLen, _CharType* destStr, int32_t destStrLen, int32_t destStrBufferSize);
    template <std::size_t _DestStrBufferSize>
    static void Append(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize], int32_t destStrLen);
    static void Append(_CharType* destStr, int32_t destStrLen, int32_t destStrBufferSize, _CharType ch, int32_t chCount = 1);
    template <std::size_t _DestStrBufferSize>
    static void Append(_CharType(&destStr)[_DestStrBufferSize], int32_t destStrLen, _CharType ch, int32_t chCount = 1);
    static int32_t IndexOf(const _CharType* str, int32_t strLen, const _CharType* subStr, int32_t subStrLen);
    template <typename _PredicateType>
    static int32_t IndexOfAny(const _CharType* str, int32_t strLen, const _PredicateType& predicate);
    static int32_t LastIndexOf(const _CharType* str, int32_t strLen, const _CharType* subStr, int32_t subStrLen);
    template <typename _PredicateType>
    static int32_t LastIndexOfAny(const _CharType* str, int32_t strLen, const _PredicateType& predicate);
    static int32_t Compare(const _CharType* lhsStr, int32_t lhsStrLen, const _CharType* rhsStr, int32_t rhsStrLen);
    static constexpr int32_t Length(const _CharType* str) noexcept;
    static void Swap(_CharType* srcStr, int32_t srcStrLen, _CharType* destStr, int32_t destStrLen);
    template <std::size_t _DestStrBufferSize>
    static void ToLower(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize]);
    template <std::size_t _DestStrBufferSize>
    static void ToUpper(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize]);
};

using StringTraits = BasicStringTraits<char>;
using U16StringTraits = BasicStringTraits<char16_t>;
using U32StringTraits = BasicStringTraits<char32_t>;
using WStringTraits = BasicStringTraits<wchar_t>;

template<typename _CharType>
template<std::size_t _DestStrBufferSize>
inline void BasicStringTraits<_CharType>::Append(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize], int32_t destStrLen)
{
    Append(srcStr, srcStrLen, destStr, destStrLen, _DestStrBufferSize);
}

template<typename _CharType>
inline void BasicStringTraits<_CharType>::Append(const _CharType* srcStr, int32_t srcStrLen, _CharType* destStr, int32_t destStrLen, int32_t destStrBufferSize)
{
    assert(destStrBufferSize > srcStrLen + destStrLen && "String buffer overflowed!");

    memcpy(&destStr[destStrLen], srcStr, sizeof(_CharType) * srcStrLen);

    destStr[srcStrLen + destStrLen] = _CharType();
}

template<typename _CharType>
template<std::size_t _DestStrBufferSize>
inline void BasicStringTraits<_CharType>::Append(_CharType(&destStr)[_DestStrBufferSize], int32_t destStrLen, _CharType ch, int32_t chCount)
{
    Append(destStr, destStrLen, _DestStrBufferSize, ch, chCount);
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Append(_CharType* destStr, int32_t destStrLen, int32_t destStrBufferSize, _CharType ch, int32_t chCount)
{
    assert(destStrBufferSize > chCount + destStrLen && "String buffer overflowed!");

    chCount += destStrLen;
    while (destStrLen < chCount)
    {
        destStr[destStrLen++] = ch;
    }

    destStr[destStrLen] = _CharType();
}

template <typename _CharType>
inline int32_t BasicStringTraits<_CharType>::IndexOf(const _CharType* str, int32_t strLen, const _CharType* subStr, int32_t subStrLen)
{
    const _CharType* foundStr = std::search(str, str + strLen, subStr, subStr + subStrLen);
    if (foundStr != str + strLen)
    {
        return static_cast<std::size_t>(foundStr - str);
    }

    return -1;
}

template<typename _CharType>
template<typename _PredicateType>
inline int32_t BasicStringTraits<_CharType>::IndexOfAny(const _CharType* str, int32_t strLen, const _PredicateType& predicate)
{
    const _CharType* foundStr = std::find_if(str, str + strLen, predicate);
    if (foundStr != str + strLen)
    {
        return static_cast<std::size_t>(foundStr - str);
    }

    return -1;
}

template <typename _CharType>
inline int32_t BasicStringTraits<_CharType>::LastIndexOf(const _CharType* str, int32_t strLen, const _CharType* subStr, int32_t subStrLen)
{
    const _CharType* foundStr = std::find_end(str, str + strLen, subStr, subStr + subStrLen);
    if (foundStr != str + strLen)
    {
        return static_cast<std::size_t>(foundStr - str);
    }

    return -1;
}

template<typename _CharType>
template<typename _PredicateType>
inline int32_t BasicStringTraits<_CharType>::LastIndexOfAny(const _CharType* str, int32_t strLen, const _PredicateType& predicate)
{
    for (int32_t i = strLen - 1; i >= 0; --i)
    {
        if (predicate(str[i]))
        {
            return i;
        }
    }

    return -1;
}

template <typename _CharType>
inline int32_t BasicStringTraits<_CharType>::Compare(const _CharType* lhsStr, int32_t lhsStrLen, const _CharType* rhsStr, int32_t rhsStrLen)
{
    auto ans = std::char_traits<_CharType>::compare(lhsStr, rhsStr, std::min(lhsStrLen, rhsStrLen));
    if (ans != 0)
    {
        return ans;
    }

    if (lhsStrLen < rhsStrLen)
    {
        return -1;
    }
    if (lhsStrLen > rhsStrLen)
    {
        return 1;
    }

    return 0;
}

template <typename _CharType>
constexpr int32_t BasicStringTraits<_CharType>::Length(const _CharType* srcStr) noexcept
{
    return static_cast<int32_t>(std::char_traits<_CharType>::length(srcStr));
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Swap(_CharType* srcStr, int32_t srcStrLen, _CharType* destStr, int32_t destStrLen)
{
    std::swap_ranges(srcStr, srcStr + srcStrLen, destStr);
}

template <typename _CharType>
template <std::size_t _DestStrBufferSize>
inline void BasicStringTraits<_CharType>::ToLower(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize])
{
    assert(_DestStrBufferSize > srcStrLen && "String buffer overflowed!");

    std::transform(srcStr, srcStr + srcStrLen, destStr, ::tolower);
}

template <typename _CharType>
template <std::size_t _DestStrBufferSize>
inline void BasicStringTraits<_CharType>::ToUpper(const _CharType* srcStr, int32_t srcStrLen, _CharType(&destStr)[_DestStrBufferSize])
{
    assert(_DestStrBufferSize > srcStrLen && "String buffer overflowed!");

    std::transform(srcStr, srcStr + srcStrLen, destStr, ::toupper);
}

}
