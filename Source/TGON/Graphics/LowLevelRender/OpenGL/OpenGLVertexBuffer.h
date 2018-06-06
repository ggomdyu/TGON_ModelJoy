/**
 * @filename    OpenGLVertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 */

#pragma once
#include <memory>
#include <vector>

#include "../Generic/GenericVertexBuffer.h"

#include "OpenGLVertexBufferType.h"

namespace tgon
{

class OpenGLVertexBuffer :
    public GenericVertexBuffer
{
/* @section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    OpenGLVertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    OpenGLVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs);
    OpenGLVertexBuffer(OpenGLVertexBuffer&&);

/* @section Public destructor */
public:
    virtual ~OpenGLVertexBuffer() override;

/* @section Public operator */
public:
    OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&&);

/* @section Public method */
public:
    virtual void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) final override;
    virtual void Use() final override;    
    virtual void Unuse() final override;
    virtual bool IsValid() const noexcept final override;

/* @section Private method */
private:
    GLuint GenerateBuffer() const;

/* @section Private variable */
private:
    GLuint m_vertexBufferHandle;
    std::vector<OpenGLVertexBufferDesc> m_vertexBufferDescs;
};

template<typename _DataArrayType, std::size_t _DataArraySize>
inline OpenGLVertexBuffer::OpenGLVertexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    OpenGLVertexBuffer(data, sizeof(data), isDynamicUsage, vertexBufferDescs)
{
}

using VertexBuffer = OpenGLVertexBuffer;

} /* namespace tgon */