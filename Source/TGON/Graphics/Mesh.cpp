#include "PrecompiledHeader.h"

#include "Mesh.h"

namespace tgon
{

Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) :
    m_vertexBuffer(vertexBuffer),
    m_indexBuffer(indexBuffer)
{
}

void Mesh::Use()
{
    if (m_vertexBuffer != nullptr)
    {
        m_vertexBuffer->Use();
    }

    if (m_indexBuffer != nullptr)
    {
        m_indexBuffer->Use();
    }
}

void Mesh::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}

void Mesh::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    m_indexBuffer = indexBuffer;
}
    
const std::shared_ptr<VertexBuffer>& Mesh::GetVertexBuffer() const noexcept
{
    return m_vertexBuffer;
}

const std::shared_ptr<IndexBuffer>& Mesh::GetIndexBuffer() const noexcept
{
    return m_indexBuffer;
}

} /* namespace tgon */