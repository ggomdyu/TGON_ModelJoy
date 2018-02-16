#include "PrecompiledHeader.pch"

#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexBufferUtility.h"

#include <cassert>

namespace tgon
{
namespace graphics
{

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs) :
    GenericVertexBuffer(dataBytes, isDynamicUsage),
    m_vertexBufferDesc(vertexBufferDescs.size()),
    m_vertexBufferHandle(GenerateBuffer())
{
    assert(data != nullptr && dataBytes != 0 && vertexBufferDescs.size() > 0);

    this->SetData(data, dataBytes, isDynamicUsage, vertexBufferDescs);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBufferHandle);
}

void OpenGLVertexBuffer::SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferDesc>& vertexBufferDescs)
{
    int index = 0;
    for (auto& vertexBufferDesc : vertexBufferDescs)
    {
        m_vertexBufferDesc[index++] = ConvertVertexBufferDescToNative(vertexBufferDesc);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, dataBytes, data, isDynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::Use()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
    auto err = glGetError();

    for (int i = 0; i < m_vertexBufferDesc.size(); ++i)
    {
        const auto& vertexBufferDesc = m_vertexBufferDesc[i];

        glEnableVertexAttribArray(i);
        err = glGetError();
        glVertexAttribPointer(
            vertexBufferDesc.attribute,
            vertexBufferDesc.dimension,
            vertexBufferDesc.type,
            vertexBufferDesc.normalized,
            vertexBufferDesc.stride,
            vertexBufferDesc.offset
        );
        err = glGetError();
    }
}

void OpenGLVertexBuffer::Unuse()
{
    for (int i = 0; i < m_vertexBufferDesc.size(); ++i)
    {
        glDisableVertexAttribArray(i);
    }
}

bool OpenGLVertexBuffer::IsValid() const noexcept
{
    return m_vertexBufferHandle != 0;
}

GLuint OpenGLVertexBuffer::GenerateBuffer() const
{
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);

    return vertexBufferHandle;
}

} /* namespace graphics */
} /* namespace tgon */