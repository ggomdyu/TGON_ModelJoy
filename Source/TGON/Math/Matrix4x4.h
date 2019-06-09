/**
 * @file    Matrix4x4.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstdint>
#include <cassert>
#include <cmath>

#include "Vector3.h"

#if _MSC_VER
#   define TGON_SPRINTF sprintf_s
#else
#   define TGON_SPRINTF snprintf
#endif

namespace tgon
{

struct Matrix4x4
{
/**@section Constructor */
public:
    /**@brief   Initializes matrix as an Identity matrix. */
    constexpr Matrix4x4() noexcept;

    /**@brief   Initializes matrix with the specified value. */
    constexpr Matrix4x4(float m00, float m01, float m02, float m03,
                        float m10, float m11, float m12, float m13,
                        float m20, float m21, float m22, float m23,
                        float m30, float m31, float m32, float m33) noexcept;

/**@section Operator */
public:
    Matrix4x4 operator+(const Matrix4x4&) const noexcept;
    Matrix4x4 operator-(const Matrix4x4&) const noexcept;
    Matrix4x4 operator*(const Matrix4x4&) const noexcept;
    Matrix4x4& operator+=(const Matrix4x4&) noexcept;
    Matrix4x4& operator-=(const Matrix4x4&) noexcept;
    Matrix4x4& operator*=(const Matrix4x4&) noexcept;
    constexpr bool operator==(const Matrix4x4&) const noexcept;
    constexpr bool operator!=(const Matrix4x4&) const noexcept;
    float* operator[](std::size_t index);
    const float* operator[](std::size_t index) const;

/**@section Method */
public:
    static constexpr const Matrix4x4 Identity() noexcept;
    static constexpr const Matrix4x4 Zero() noexcept;
    static constexpr const Matrix4x4 Translate(float x, float y, float z) noexcept;
    static const Matrix4x4 Rotate(float yaw, float pitch, float roll) noexcept;
    static const Matrix4x4 RotateX(float radian) noexcept;
    static const Matrix4x4 RotateY(float radian) noexcept;
    static const Matrix4x4 RotateZ(float radian) noexcept;
    static constexpr const Matrix4x4 Scale(float x, float y, float z) noexcept;
    static constexpr const Matrix4x4 Transposed(const Matrix4x4& matrix) noexcept;
    void Transpose() noexcept;
    static constexpr const Matrix4x4 Inverse();
    static Matrix4x4 LookAtLH(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up) noexcept;
    static Matrix4x4 LookAtRH(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up) noexcept;
    static Matrix4x4 PerspectiveLH(float fovy, float aspect, float nearZ, float farZ) noexcept;
    static Matrix4x4 PerspectiveRH(float fovy, float aspect, float nearZ, float farZ) noexcept;
    static constexpr Matrix4x4 OrthographicRH(float left, float right, float top, float bottom, float nearZ, float farZ) noexcept;
    static constexpr Matrix4x4 Viewport(float x, float y, float width, float height, float minZ, float maxZ) noexcept;

    /**
     * @brief   Creates a string that represents this Matrix.
     * @param [out] destStr     The destination of the string to be written.
     * @return  The length of string.
     */
    template <std::size_t _StrBufferSize>
    int32_t ToString(char(&destStr)[_StrBufferSize]) const;

    /**
     * @brief   Creates a string that represents this Matrix.
     * @param [out] destStr         The destination of the string to be written.
     * @param [in] strBufferSize    The buffer size of destStr.
     * @return  The length of string.
     */
    int32_t ToString(char* destStr, std::size_t strBufferSize) const;

/**@section Variable */
public:
    float m00, m01, m02, m03,
          m10, m11, m12, m13,
          m20, m21, m22, m23,
          m30, m31, m32, m33;
};

constexpr Matrix4x4::Matrix4x4() noexcept :
    m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
    m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
{
}

constexpr Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
                               float m10, float m11, float m12, float m13,
                               float m20, float m21, float m22, float m23,
                               float m30, float m31, float m32, float m33) noexcept :
    m00(m00), m01(m01), m02(m02), m03(m03),
    m10(m10), m11(m11), m12(m12), m13(m13),
    m20(m20), m21(m21), m22(m22), m23(m23),
    m30(m30), m31(m31), m32(m32), m33(m33)
{
}

inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const noexcept
{
    return Matrix4x4(
        m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02, m03 - rhs.m03,
        m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
        m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
        m30 - rhs.m30, m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33
    );
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const noexcept
{
    return Matrix4x4(
        (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20) + (m03 * rhs.m30),
        (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21) + (m03 * rhs.m31),
        (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22) + (m03 * rhs.m32),
        (m00 * rhs.m03) + (m01 * rhs.m13) + (m02 * rhs.m23) + (m03 * rhs.m33),

        (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20) + (m13 * rhs.m30),
        (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21) + (m13 * rhs.m31),
        (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22) + (m13 * rhs.m32),
        (m10 * rhs.m03) + (m11 * rhs.m13) + (m12 * rhs.m23) + (m13 * rhs.m33),

        (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20) + (m23 * rhs.m30),
        (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21) + (m23 * rhs.m31),
        (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22) + (m23 * rhs.m32),
        (m20 * rhs.m03) + (m21 * rhs.m13) + (m22 * rhs.m23) + (m23 * rhs.m33),

        (m30 * rhs.m00) + (m31 * rhs.m10) + (m32 * rhs.m20) + (m33 * rhs.m30),
        (m30 * rhs.m01) + (m31 * rhs.m11) + (m32 * rhs.m21) + (m33 * rhs.m31),
        (m30 * rhs.m02) + (m31 * rhs.m12) + (m32 * rhs.m22) + (m33 * rhs.m32),
        (m30 * rhs.m03) + (m31 * rhs.m13) + (m32 * rhs.m23) + (m33 * rhs.m33)
    );
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs) noexcept
{
    m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
    m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
    m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
    m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;

    return *this;
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs) noexcept
{
    m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
    m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
    m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
    m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;

    return *this;
}

inline Matrix4x4 Matrix4x4::LookAtLH(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up) noexcept
{
    Vector3 l = lookAt - eyePt;
    l.Normalize();
    
    Vector3 r = Vector3::Cross(up, l);
    r.Normalize();

    Vector3 u = Vector3::Cross(l, r);
    u.Normalize();

    return Matrix4x4(
        r.x, u.x, l.x, 0.f,
        r.y, u.y, l.y, 0.f,
        r.z, u.z, l.z, 0.f,
        -Vector3::Dot(r, eyePt), -Vector3::Dot(u, eyePt), -Vector3::Dot(l, eyePt), 1.f
    );
}

inline Matrix4x4 Matrix4x4::LookAtRH(const Vector3& eyePt, const Vector3& lookAt, const Vector3& up) noexcept
{
    Vector3 l = lookAt - eyePt;
    l.Normalize();

    Vector3 r = Vector3::Cross(l, up);
    r.Normalize();

    Vector3 u = Vector3::Cross(r, l);
    u.Normalize();
    
    return Matrix4x4(
        r.x, u.x, -l.x, 0.f,
        r.y, u.y, -l.y, 0.f,
        r.z, u.z, -l.z, 0.f,
        -Vector3::Dot(r, eyePt), -Vector3::Dot(u, eyePt), Vector3::Dot(l, eyePt), 1.f
    );
}

inline Matrix4x4 Matrix4x4::PerspectiveLH(float fovy, float aspect, float nearZ, float farZ) noexcept
{
    float scaleY = 1.0f / std::tan(fovy * 0.5f);
    float scaleX = scaleY / aspect;

    return Matrix4x4(
        scaleX, 0.0f,   0.0f,                               0.0f,
        0.0f,   scaleY, 0.0f,                               0.0f,
        0.0f,   0.0f,   farZ / (farZ - nearZ),              1.0f,
        0.0f,   0.0f,   -(farZ * nearZ) / (farZ - nearZ),   0.0f
    );
}

inline Matrix4x4 Matrix4x4::PerspectiveRH(float fovy, float aspect, float nearZ, float farZ) noexcept
{
    float scaleY = 1.0f / std::tan(fovy * 0.5f);
    float scaleX = scaleY / aspect;

    return Matrix4x4(
        scaleX, 0.0f,   0.0f,                               0.0f,
        0.0f,   scaleY, 0.0f,                               0.0f,
        0.0f,   0.0f,   farZ / (nearZ - farZ),              -1.0f,
        0.0f,   0.0f,   -(farZ * nearZ) / (farZ - nearZ),   0.0f
    );
}
    
constexpr Matrix4x4 Matrix4x4::OrthographicRH(float left, float right, float top, float bottom, float nearZ, float farZ) noexcept
{
    float width = right - left;
    float height = bottom - top;
    float depth = farZ - nearZ;
    
    return Matrix4x4(
        2 / width,  0.0f,           0.0f,               0.0f,
        0.0f,       2 / height,     0.0f,               0.0f,
        0.0f,       0.0f,           -2.0f / depth,      0.0f,
        -(right + left) / width,    -(top + bottom) / height,   -(farZ + nearZ) / depth,    1.0f
    );
}

constexpr Matrix4x4 Matrix4x4::Viewport(float x, float y, float width, float height, float minZ, float maxZ) noexcept
{
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    return Matrix4x4(
        halfWidth,      0.0f,           0.0f,           0.0f,
        0.0f,           -halfHeight,    0.0f,           0.0f,
        0.0f,           0.0f,           maxZ - minZ,    0.0f,
        x + halfWidth,  y + halfHeight, minZ,           1.0f
    );
}

constexpr const Matrix4x4 Matrix4x4::Transposed(const Matrix4x4& matrix) noexcept
{
    return Matrix4x4(
        matrix.m00, matrix.m10, matrix.m20, matrix.m30,
        matrix.m01, matrix.m11, matrix.m21, matrix.m31,
        matrix.m02, matrix.m12, matrix.m22, matrix.m32,
        matrix.m03, matrix.m13, matrix.m23, matrix.m33
    );
}

inline void Matrix4x4::Transpose() noexcept
{
    *this = Transposed(*this);
}

//#if TGON_SUPPORT_SSE 1
//inline Matrix4x4::Matrix4x4()
//{
//    _mm_storeu_ps(&m00, _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
//    _mm_storeu_ps(&m10, _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f));
//    _mm_storeu_ps(&m20, _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f));
//    _mm_storeu_ps(&m30, _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f));
//}
//#else
//inline Matrix4x4::Matrix4x4() :
//    m00(1.0f), m01(0.0f), m02(0.0f), m03(0.0f),
//    m10(0.0f), m11(1.0f), m12(0.0f), m13(0.0f),
//    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
//    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
//{
//}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const noexcept
{
//#if TGON_SUPPORT_SSE
//    Matrix4x4 ret;
//
//    _mm_storeu_ps(&ret.m00, _mm_add_ps(_mm_loadu_ps(&m00), _mm_loadu_ps(&rhs.m00)));
//    _mm_storeu_ps(&ret.m10, _mm_add_ps(_mm_loadu_ps(&m10), _mm_loadu_ps(&rhs.m10)));
//    _mm_storeu_ps(&ret.m20, _mm_add_ps(_mm_loadu_ps(&m20), _mm_loadu_ps(&rhs.m20)));
//    _mm_storeu_ps(&ret.m30, _mm_add_ps(_mm_loadu_ps(&m30), _mm_loadu_ps(&rhs.m30)));
//
//    return ret;
//#else
    return Matrix4x4(
        m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02, m03 + rhs.m03,
        m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
        m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
        m30 + rhs.m30, m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33
    );
//#endif
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs) noexcept
{
    *this = (*this) * rhs;
    return *this;
}

constexpr bool Matrix4x4::operator==(const Matrix4x4& rhs) const noexcept
{
    for (int i = 0; i < 16; ++i)
    {
        if ((&(m00))[i] != (&(rhs.m00))[i])
        {
            return false;
        }
    }
    return true;
}

constexpr bool Matrix4x4::operator!=(const Matrix4x4& rhs) const noexcept
{
    return !this->operator==(rhs);
}

inline float* Matrix4x4::operator[](std::size_t index)
{
    return &m00 + (index * 4);
}

inline const float* Matrix4x4::operator[](std::size_t index) const
{
    return const_cast<Matrix4x4*>(this)->operator[](index);
}

constexpr const Matrix4x4 Matrix4x4::Translate(float x, float y, float z) noexcept
{
    return Matrix4x4(
        1.0f,   0.0f,   0.0f,   0.0f,
        0.0f,   1.0f,   0.0f,   0.0f,
        0.0f,   0.0f,   1.0f,   0.0f,
        x,      y,      z,      1.0f
    );
}

constexpr const Matrix4x4 Matrix4x4::Identity() noexcept
{
    return Matrix4x4(
        1.f,    0.f,    0.f,    0.f,
        0.f,    1.f,    0.f,    0.f,
        0.f,    0.f,    1.f,    0.f,
        0.f,    0.f,    0.f,    1.f
    );
}

constexpr const Matrix4x4 Matrix4x4::Zero() noexcept
{
    return Matrix4x4(
        0.f,    0.f,    0.f,    0.f,
        0.f,    0.f,    0.f,    0.f,
        0.f,    0.f,    0.f,    0.f,
        0.f,    0.f,    0.f,    0.f
    );
}

inline const Matrix4x4 Matrix4x4::Rotate(float yaw, float pitch, float roll) noexcept
{
    float cosA = std::cos(yaw);
    float sinA = std::sin(yaw);
    
    float cosB = std::cos(pitch);
    float sinB = std::sin(pitch);
    
    float cosC = std::cos(roll);
    float sinC = std::sin(roll);
    
    return Matrix4x4(
        cosB * cosC,                            cosB * -sinC,                           sinB,           0.0f,
        (sinA * sinB * cosC) + (cosA * sinC),   (sinA * sinB * -sinC) + (cosA * cosC),  -sinA * cosB,   0.0f,
        (cosA * -sinB * cosC) + (sinA * sinC),  (cosA * sinB * sinC) + (sinA * cosC),   cosA * cosB,    0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    );
}

inline const Matrix4x4 Matrix4x4::RotateX(float radian) noexcept
{
    float cosA = std::cos(radian);
    float sinA = std::sin(radian);

    return Matrix4x4(
        1.0f,   0.0f,   0.0f,   0.0f,
        0.0f,   cosA,   -sinA,  0.0f,
        0.0f,   sinA,   cosA,   0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    );
}

inline const Matrix4x4 Matrix4x4::RotateY(float radian) noexcept
{
    float cosA = std::cos(radian);
    float sinA = std::sin(radian);

    return Matrix4x4(
        cosA,   0.0f,   sinA,   0.0f,
        0.0f,   1.0f,   0.0f,   0.0f,
        -sinA,  0.0f,   cosA,   0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    );
}

inline const Matrix4x4 Matrix4x4::RotateZ(float radian) noexcept
{
    float cosA = std::cos(radian);
    float sinA = std::sin(radian);

    return Matrix4x4(
        cosA,   -sinA,   0.0f,   0.0f,
        sinA,   cosA,   0.0f,   0.0f,
        0.0f,   0.0f,   1.0f,   0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    );
}

constexpr const Matrix4x4 Matrix4x4::Scale(float x, float y, float z) noexcept
{
    return Matrix4x4(
        x,      0.0f,   0.0f,   0.0f,
        0.0f,   y,      0.0f,   0.0f,
        0.0f,   0.0f,   z,      0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    );
}

template<std::size_t _StrBufferSize>
inline int32_t Matrix4x4::ToString(char(&destStr)[_StrBufferSize]) const
{
    this->ToString(destStr, sizeof(destStr));
}

inline int32_t Matrix4x4::ToString(char * destStr, std::size_t strBufferSize) const
{
    return TGON_SPRINTF(destStr, sizeof(destStr[0]) * strBufferSize, "%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f", m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
}

} /* namespace tgon */

#undef TGON_SPRINTF