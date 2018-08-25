/**
 * @file    OpenGLVertexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>

#include "../VertexBufferType.h"

namespace tgon
{

class VertexBufferImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    /**
     * @brief                               Sets the vertex buffer with the specified data.
     * @param [in] data                     The data to store in the vertex buffer.
     * @param [in] dataBytes                The byte size of the data.
     * @param [in] isDynamicUsage           If true, then the index buffer will not be modified after set.
     * @param [in] vertexBufferLayoutDescs  The vertex layout descriptors.
     */
    VertexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);

    VertexBufferImpl(VertexBufferImpl&& rhs);

/* @section Public destructor */
public:
    ~VertexBufferImpl();

/* @section Public method */
public:
    /**
     * @brief                               Sets the vertex buffer with the specified data.
     * @param [in] data                     The data to store in the vertex buffer.
     * @param [in] dataBytes                The byte size of the data.
     * @param [in] isDynamicUsage           If true, then the index buffer will not be modified after set.
     * @param [in] vertexBufferLayoutDescs  The vertex layout descriptors.
     */
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage, const std::initializer_list<VertexBufferLayoutDescriptor>& vertexBufferLayoutDescs);
    
    /* @brief                               Gets the byte size of the data stored in the buffer.  */
    std::size_t GetDataBytes() const noexcept;
    
    /* @brief                               Sets the rendering pipeline to use this buffer. */
    void Use();
    
    /* @brief                               Sets the rendering pipeline does not use this buffer. */
    void Unuse();
    
    /**
     * @brief                               Checks the buffer was created successfully.
     * @return                              Returns true if the buffer was created successfully, false otherwise.
     */
    bool IsValid() const noexcept;
    
    bool IsDynamicUsage() const noexcept;

/* @section Private method */
private:
    GLuint CreateVertexBufferHandle() const;

/* @section Private variable */
private:
    std::size_t m_dataBytes;
    bool m_isDynamicUsage;
    GLuint m_vertexBufferHandle;
    std::vector<VertexBufferLayoutDescriptor> m_vertexBufferLayoutDescs;
};

} /* namespace tgon */
