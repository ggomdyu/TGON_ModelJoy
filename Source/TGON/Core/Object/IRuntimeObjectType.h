/**
 * @filename    IRuntimeObjectType.h
 * @author      ggomdyu
 * @since       10/29/2017
 */

#pragma once
#include <typeinfo>
#include <cstdint>

namespace tgon
{
namespace object
{

struct RTTI final
{
/* @section Public constructor */
public:
    RTTI(const std::type_info& rawRTTI, const RTTI* superRTTI) noexcept;

/* @section Public method */
public:
    std::size_t GetHashCode() const noexcept;
    const char* GetName() const noexcept;

    const RTTI* GetSuperRTTI() const noexcept;

/* @section Private variable */
private:
    const std::type_info& m_rawRTTI;
    const RTTI* m_superRTTI;
};

inline RTTI::RTTI(const std::type_info& rawRTTI, const RTTI* superRTTI) noexcept :
    m_rawRTTI(rawRTTI),
    m_superRTTI(superRTTI)
{
}

inline std::size_t RTTI::GetHashCode() const noexcept
{
    return m_rawRTTI.hash_code();
}

inline const char* RTTI::GetName() const noexcept
{
    return m_rawRTTI.name();
}

inline const RTTI* RTTI::GetSuperRTTI() const noexcept
{
    return m_superRTTI;
}

} /* namespace object */
} /* namespace tgon */