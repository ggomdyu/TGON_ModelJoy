/**
 * @file    Camera.h
 * @author  ggomdyu
 * @since   09/01/2017
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Vector3.h"

#include "../LowLevel/GraphicsType.h"

#include "CameraType.h"

namespace tgon
{

class TGON_API Camera
{
/* @section Public constructor */
public:
    Camera() noexcept;

    Camera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ, ProjectionMode projectionMode, FillMode fillMode, CullMode cullMode) noexcept;

/* @section Public method */
public:
    void Update();
    
    /* @brief   Sets the near clipping plane's Z-position. */
    void SetNearZ(float nearZ) noexcept;
    
    /* @brief   Sets the far clipping plane's Z-position. */
    void SetFarZ(float farZ) noexcept;
    
    /* @brief   Sets the field of view. */
    void SetFov(float fov) noexcept;
    
    void SetProjectionMode(ProjectionMode projectionMode) noexcept;
    
    /* @brief   Sets the position of camera. */
    void SetEyePt(const Vector3& eyePt) noexcept;
    
    /* @brief   Sets the direction vector of camera. */
    void SetLookAt(const Vector3& lookAt) noexcept;
    
    void SetFillMode(FillMode fillMode) noexcept;
    
    void SetCullMode(CullMode cullMode) noexcept;
    
    /* @brief   Gets the near clipping plane's Z-position. */
    float GetNearZ() const noexcept;
    
    /* @brief   Gets the far clipping plane's Z-position. */
    float GetFarZ() const noexcept;
    
    /* @brief   Gets the field of view. */
    float GetFov() const noexcept;
    
    ProjectionMode GetProjectionMode() const noexcept;
    
    /* @brief   Gets the view projection matrix which is updated each frame. */
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;
    
    /* @brief   Gets the position of camera. */
    const Vector3& GetEyePt() const noexcept;
    
    /* @brief   Gets the direction vector of camera. */
    const Vector3& GetLookAt() const noexcept;
    
    FillMode GetFillMode() const noexcept;
    
    CullMode GetCullMode() const noexcept;

/* @section Private variable */
private:
    Vector3 m_eyePt;
    Vector3 m_lookAt;
    float m_fov;
    float m_nearZ;
    float m_farZ;
    Matrix4x4 m_matViewProj;
    bool m_isDirty;
    ProjectionMode m_projectionMode;
    FillMode m_fillMode;
    CullMode m_cullMode;
};

} /* namespace tgon */
