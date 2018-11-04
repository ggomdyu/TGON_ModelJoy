/**
 * @file    View.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>

#include "Core/Object/CoreObject.h"
#include "Core/Object/DelegateChain.h"
#include "Graphics/LowLevel/Graphics.h"

#include "Batch.h"
#include "SpriteBatch.h"

namespace tgon
{

class Window;
struct VideoMode;

class TGON_API View final :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(View);

/**@section Public constructor */
public:
    explicit View(const Window& displayWindow, const VideoMode& videoMode);

/**@section Public method */
public:
    /**@brief   Adds a mesh into the BatchGroup. */
    //void AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive);
    
    /**@brief   Adds a batch into the BatchGroup. */
    //void AddBatch(const Batch& batch);

    /**@brief   Adds a sprite batch into the SpriteBatchGroup. */
    void AddSpriteBatch(const std::shared_ptr<TextureMaterial>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);

    /**@brief   Adds a batch into the SpriteBatchGroup. */
    void AddSpriteBatch(const SpriteBatch& batch);

    /**@brief   Adds a camera into View. */
    void AddCamera(const std::shared_ptr<Camera>& camera);

    std::vector<std::shared_ptr<Camera>>& GetCameraList() noexcept;

    const std::vector<std::shared_ptr<Camera>>& GetCameraList() const noexcept;

    /**@brief   Removes the specified camera in View. */
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
    void Draw();

/**@section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnResizeView;

/**@section Private variable */
private:
    Graphics m_graphics;

    //BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
