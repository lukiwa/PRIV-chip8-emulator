#include "VertexArray.h"
#include "Tracing.h"

/**
 * Create vertex array
 */
VertexArray::VertexArray()
    : _id(1)
{

    GlAssert(glGenVertexArrays(1, &_id));
    GlAssert(glBindVertexArray(_id));
}

/**
 * Destroy (delete) buffer
 */
VertexArray::~VertexArray()
{
    GlAssert(glDeleteVertexArrays(1, &_id));
}

/**
 * Bind buffer
 */
void VertexArray::Bind() const
{
    GlAssert(glBindVertexArray(_id));
}

/**
 * Undbind buffer
 */
void VertexArray::Unbind() const
{
    GlAssert(glBindVertexArray(0));
}
