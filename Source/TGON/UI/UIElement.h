/**
 * @file    UIElement.h
 * @author  ggomdyu
 * @since   11/20/2019
 */

#pragma once
#include <vector>

#include "Core/NonCopyable.h"

#include "UIBatch.h"

namespace tgon
{

class UIElement :
    private NonCopyable
{
/**@section Destructor */
public:
    virtual ~UIElement() = default;
    
/**@section Method */
public:
    virtual void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const = 0;
};

} /* namespace tgon */