#include "PrecompiledHeader.h"

#include "Platform/Application.h"
#include "Engine/GraphicsModule.h"
#include "Graphics/Camera.h"

#include "CameraComponent.h"

namespace tgon
{

CameraComponent::CameraComponent() :
    CameraComponent(std::make_shared<Camera>())
{
}

CameraComponent::CameraComponent(const FRect& orthoPlane, float nearZ, float farZ) :
    CameraComponent(std::make_shared<Camera>(orthoPlane, nearZ, farZ))
{
}

CameraComponent::CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) :
    CameraComponent(std::make_shared<Camera>(eyePt, lookAt, fov, nearZ, farZ))
{
}

CameraComponent::CameraComponent(const std::shared_ptr<Camera>& camera) :
    m_camera(camera),
    m_graphicsModule(Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>())
{
    auto graphicsModule = m_graphicsModule.lock();
    if (graphicsModule != nullptr)
    {
        graphicsModule->GetCanvasRenderer().AddCamera(camera);
    }
}

CameraComponent::~CameraComponent()
{
    auto graphicsModule = m_graphicsModule.lock();
    if (graphicsModule != nullptr)
    {
        graphicsModule->GetCanvasRenderer().RemoveCamera(m_camera);
    }
}

void CameraComponent::Update()
{
    m_camera->Update();
}

std::shared_ptr<Camera>& CameraComponent::GetCamera() noexcept
{
    return m_camera;
}

std::shared_ptr<const Camera> CameraComponent::GetCamera() const noexcept
{
    return m_camera;
}

} /* namespace tgon */