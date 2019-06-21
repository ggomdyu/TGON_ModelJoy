/**
 * @file    LogoScene.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "Game/Scene.h"

namespace tgon
{

class CameraComponent;
class CanvasSpriteRendererComponent;
class GraphicsModule;
class InputModule;
class TimeModule;

} /* namespace tgon */

class TGON_API LogoScene :
    public tgon::Scene
{
public:
    TGON_DECLARE_RTTI(LogoScene);

/**@section Constructor */
public:
    LogoScene();
    
/**@section Method */
public:
    virtual void Update() override;
    
    void InitPhase1();
    void InitPhase2();

    void OnHandleInput();

/**@section Variable */
private:
    int64_t m_beginTime;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_introSpriteComponent1;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_introSpriteComponent2;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_introSpriteComponent3;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_introSpriteComponent4;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_introSpriteComponent5;
    std::shared_ptr<tgon::CanvasSpriteRendererComponent> m_fadeOutSpriteComponent;
};
