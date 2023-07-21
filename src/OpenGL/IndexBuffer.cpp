#include "IndexBuffer.h"
#include "Tracing.h"

/**
 * Create buffer
 * @param data index buffer data
 * @param size number of indices
 */
IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
    : _id(0)
    , _count(count)
{
    GlAssert(glGenBuffers(1, &_id));
    GlAssert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
    GlAssert(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

/**
 * Destroy (delete) buffer
 */
IndexBuffer::~IndexBuffer()
{
    GlAssert(glDeleteBuffers(1, &_id));
}

/**
 * Bind buffer
 */
void IndexBuffer::Bind() const
{
    GlAssert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

/**
 * Undbind buffer
 */
void IndexBuffer::Unbind() const
{
    GlAssert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
