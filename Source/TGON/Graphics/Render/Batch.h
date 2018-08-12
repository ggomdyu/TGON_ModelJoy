/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

#include "../LowLevel/Graphics.h"

namespace tgon
{

class TGON_API Batch final
{
/* @section Public struct */
public:
    struct DrawPrimitive
    {
        std::shared_ptr<Mesh> mesh;
        const Matrix4x4* matWVP;
    };

/* @section Public constructor */
public:
    /* @brief   Initializes the batch with a material. */
    explicit Batch(const std::shared_ptr<Material>& material);
    
    /* @brief   Initializes the batch with a material and primitives. */
    explicit Batch(const std::shared_ptr<Material>& material, const std::initializer_list<DrawPrimitive>& drawPrimitives);

/* @section Public method */
public:
    /* @brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const std::shared_ptr<Mesh>& mesh, const Matrix4x4* matWVP);
    
    /* @brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const DrawPrimitive& drawPrimitive);

    /* @brief   Checks whether the specified material can batched. */
    bool CanBatch(const std::shared_ptr<Material>& material) const;
    
    /* @brief   Draws all batched primitives. */
    void Draw(Graphics& graphics, const Camera& camera);

/* @section Private variable */
private:
    std::shared_ptr<Material> m_material;
    
    std::vector<DrawPrimitive> m_drawPrimitives;
};
    
class TGON_API BatchGroup final
{
/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch list. */
    void AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive);
    
    /* @brief   Adds a batch into the batch list. */
    void AddBatch(const Batch& batch);
    
    /* @brief   Flushes all the batch in list. */
    void FlushBatch(Graphics& graphics, const Camera& camera);

/* @section Private variable */
private:
    std::vector<Batch> m_batches;
};
    
} /* namespace tgon */
