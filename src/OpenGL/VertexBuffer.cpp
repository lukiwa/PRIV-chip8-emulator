//
// Created by shaux on 27.07.2021.
//

#include "VertexBuffer.h"
#include "Tracing.h"

/**
 * Create buffer
 * @param data vertex data
 * @param size vertex size
 */
VertexBuffer::VertexBuffer(const void* data, uint32_t size)
    : _id(0)
{
    GlAssert(glGenBuffers(1, &_id));
    GlAssert(glBindBuffer(GL_ARRAY_BUFFER, _id));
    GlAssert(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

/**
 * Destroy (delete) buffer
 */
VertexBuffer::~VertexBuffer()
{
    GlAssert(glDeleteBuffers(1, &_id));
}

/**
 * Bind buffer
 */
void VertexBuffer::Bind() const
{
    GlAssert(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

/**
 * Undbind buffer
 */
void VertexBuffer::Unbind() const
{
    GlAssert(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
