/**
 * @file    SceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Game/Scene.h"

#include "Module.h"

namespace tgon
{

class SceneModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(SceneModule)

/**@section Method */
public:
    template <typename _SceneType, typename... _Args>
    void ChangeScene(_Args&&... args);
    void Update() override;

/**@section Variable */
private:
    std::unique_ptr<Scene> m_currScene;
    std::unique_ptr<Scene> m_nextScene;
};

template <typename _SceneType, typename ..._Args>
inline void SceneModule::ChangeScene(_Args&&... args)
{
    // If there's no scene, then initialize it immediately.
    if (m_currScene == nullptr)
    {
        m_currScene = std::make_unique<_SceneType>(std::forward<_Args>(args)...);
        m_currScene->Initialize();
        return;
    }
    
    // Otherwise, the scene will be initialized on next frame.
    m_nextScene = std::make_unique<_SceneType>(std::forward<_Args>(args)...);
}

} /* namespace tgon */
