/**
 * @file    DynamicCast.h
 * @author  ggomdyu
 * @since   08/17/2017
 */

#pragma once
#include <type_traits>

#include "RTTI.h"

namespace tgon
{

template <typename _CastToType, typename _CastFromType, typename std::enable_if<std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType&& ptr) noexcept
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if<!std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType&& ptr) noexcept
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<_CastToType>())
        {
            return reinterpret_cast<_CastToType>(std::forward<_CastFromType>(ptr));
        }
        else
        {
            rtti = rtti->GetSuperRTTI();
        }
    }
    
    return nullptr;
}

} /* namespace tgon */