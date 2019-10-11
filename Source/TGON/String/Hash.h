/**
 * @file    Hash.h
 * @author  ggomdyu
 * @since   03/04/2017
 */

#pragma once
#include <cstdint>
#include <cstddef>

#include "Core/TypeTraits.h"

namespace tgon
{

template <typename _CharType, typename std::enable_if_t<IsCharValue<_CharType>>* = nullptr>
constexpr uint32_t X65599Hash(_CharType ch) noexcept
{
    return ch ^ (ch >> 16);
}
    
template <typename _CharType>
constexpr uint32_t X65599Hash(const _CharType* str) noexcept
{
    if (str == nullptr)
    {
        return 0;
    }
    
    uint32_t hashValue = 0;
    for (uint32_t i = 0; str[i] != 0; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace tgon */
