/**
 * @file    Color.h
 * @author  ggomdyu
 * @since   05/03/2017
 */

#pragma once
#include <cstdint>
#include <cstdio>
#include <gsl/span>

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF snprintf
#endif

namespace tgon
{

struct Color4b
{
/**@section Constructor */
public:
    constexpr Color4b() noexcept = default;
    constexpr Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;
    constexpr Color4b(uint32_t color) noexcept;

/**@section Operator */
public:
    constexpr const Color4b operator+(const Color4b& rhs) const noexcept;
    constexpr const Color4b operator-(const Color4b& rhs) const noexcept;
    constexpr const Color4b operator*(const Color4b& rhs) const noexcept;
    template <typename _ValueType>
    constexpr const Color4b operator*(const _ValueType& rhs) const noexcept;
    template <typename _ValueType>
    friend constexpr const Color4b operator*(const _ValueType& lhs, const Color4b& rhs) noexcept;
    template <typename _ValueType>
    constexpr const Color4b operator/(const _ValueType& rhs) const noexcept;
    Color4b& operator+=(const Color4b& rhs) noexcept;
    Color4b& operator-=(const Color4b& rhs) noexcept;
    Color4b& operator*=(const Color4b& rhs) noexcept;
    template <typename _ValueType>
    Color4b& operator*=(const _ValueType& rhs) noexcept;
    Color4b& operator/=(const Color4b& rhs) noexcept;
    template <typename _ValueType>
    Color4b& operator/=(const _ValueType& rhs) noexcept;
    constexpr bool operator==(const Color4b& rhs) const noexcept;
    constexpr bool operator!=(const Color4b& rhs) const noexcept;
    constexpr operator uint32_t() const noexcept;
    
/**@section Method */
public:
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    std::string ToString() const;
    
/**@section Variable */
public:
    union
    {
        uint32_t color{};
        struct { uint8_t r, g, b, a; };
    };
};

constexpr Color4b::Color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

constexpr Color4b::Color4b(uint32_t color) noexcept :
    color(color)
{
}

constexpr const Color4b Color4b::operator+(const Color4b& rhs) const noexcept
{
    return Color4b(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}

constexpr const Color4b Color4b::operator-(const Color4b& rhs) const noexcept
{
    return Color4b(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}

constexpr const Color4b Color4b::operator*(const Color4b& rhs) const noexcept
{
    return Color4b(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
}
    
template <typename _ValueType>
constexpr const Color4b Color4b::operator*(const _ValueType& rhs) const noexcept
{
    return Color4b(r * rhs, g * rhs, b * rhs, a * rhs);
}

template <typename _ValueType>
constexpr const Color4b operator*(const _ValueType& lhs, const Color4b& rhs) noexcept
{
    return Color4b(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a);
}

template <typename _ValueType>
constexpr const Color4b Color4b::operator/(const _ValueType& rhs) const noexcept
{
    return Color4b(r / rhs, g / rhs, b / rhs, a / rhs);
}

inline Color4b& Color4b::operator+=(const Color4b& rhs) noexcept
{
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;

    return *this;
}

inline Color4b& Color4b::operator-=(const Color4b& rhs) noexcept
{
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;

    return *this;
}

inline Color4b& Color4b::operator*=(const Color4b& rhs) noexcept
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;

    return *this;
}

template <typename _ValueType>
inline Color4b& Color4b::operator*=(const _ValueType& rhs) noexcept
{
    r *= rhs;
    g *= rhs;
    b *= rhs;
    a *= rhs;

    return *this;
}

inline Color4b& Color4b::operator/=(const Color4b& rhs) noexcept
{
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;

    return *this;
}

template <typename _ValueType>
inline Color4b& Color4b::operator/=(const _ValueType& rhs) noexcept
{
    r /= rhs;
    g /= rhs;
    b /= rhs;
    a /= rhs;

    return *this;
}

constexpr bool Color4b::operator==(const Color4b& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

constexpr bool Color4b::operator!=(const Color4b& rhs) const noexcept
{
    return !this->Color4b::operator==(rhs);
}

constexpr Color4b::operator uint32_t() const noexcept
{
    return color;
}

inline int32_t Color4b::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

inline int32_t Color4b::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%d %d %d %d", r, g, b, a);
}

inline std::string Color4b::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

struct Color3f
{
/**@section Constructor */
public:
    constexpr Color3f() noexcept = default;
    constexpr Color3f(float r, float g, float b) noexcept;

/**@section Operator */
public:
    constexpr bool operator==(const Color3f& rhs) const noexcept;
    constexpr bool operator!=(const Color3f& rhs) const noexcept;

/**@section Method */
public:
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    std::string ToString() const;

/**@section Variable */
public:
    float r{}, g{}, b{};
};

constexpr Color3f::Color3f(float r, float g, float b) noexcept :
    r(r),
    g(g),
    b(b)
{
}

constexpr bool Color3f::operator==(const Color3f& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b;
}

constexpr bool Color3f::operator!=(const Color3f& rhs) const noexcept
{
    return !this->operator==(rhs);
}

inline int32_t Color3f::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

inline int32_t Color3f::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f %f", r, g, b);
}

inline std::string Color3f::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

struct Color4f
{
/**@section Constructor */
public:
    constexpr Color4f() noexcept = default;
    constexpr Color4f(float r, float g, float b, float a) noexcept;

/**@section Operator */
public:
    constexpr bool operator==(const Color4f& rhs) const noexcept;
    constexpr bool operator!=(const Color4f& rhs) const noexcept;

/**@section Method */
public:
    int32_t ToString(const gsl::span<char>& destStr) const;
    int32_t ToString(char* destStr, std::size_t destStrBufferLen) const;
    std::string ToString() const;

/**@section Variable */
public:
    float r{}, g{}, b{}, a{};
};

constexpr Color4f::Color4f(float r, float g, float b, float a) noexcept :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

constexpr bool Color4f::operator==(const Color4f& rhs) const noexcept
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

constexpr bool Color4f::operator!=(const Color4f& rhs) const noexcept
{
    return !this->operator==(rhs);
}

inline int32_t Color4f::ToString(const gsl::span<char>& destStr) const
{
    return this->ToString(&destStr[0], destStr.size());
}

inline int32_t Color4f::ToString(char* destStr, std::size_t destStrBufferLen) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * destStrBufferLen, "%f %f %f %f", r, g, b, a);
}

inline std::string Color4f::ToString() const
{
    std::array<char, 1024> str;
    int32_t strLen = this->ToString(str);
    return {&str[0], static_cast<size_t>(strLen)};
}

} /* namespace tgon */

#undef TGON_SPRINTF