#include "VertexAttributes.h"

VertexAttributes::VertexAttributes()
    : _stride(0)
    , _lastOffset(0)
{
}

/**
 * Bind vertex attributes
 */
void VertexAttributes::Bind() const
{

    _lastOffset = 0;
    for (std::size_t i = 0; i < _attributes.size(); ++i) {
        const auto& attribute = _attributes[i];
        GlAssert(glEnableVertexAttribArray(i));
        GlAssert(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, _stride,
            reinterpret_cast<const void*>(_lastOffset)));
        _lastOffset += attribute.count * GlTypeToSize(attribute.type);
    }
}

void VertexAttributes::Unbind() const
{
    for (std::size_t i = 0; i < _attributes.size(); ++i) {
        glDisableVertexAttribArray(i);
    }
}

/**
 * Do not normalize!!!
 * @param count
 * @param type
 */
void VertexAttributes::AddAttribute(uint32_t count, GLenum type)
{
    VertexAttributeElement attribute = { count, type, GL_FALSE };
    _stride += count * GlTypeToSize(type);
    _attributes.push_back(attribute);
}

/**
 * Convert GLType (eg. GL_FLOAT to sizeof type - eg. sizeof(float))
 * @param type GL type
 * @return size of type
 */
uint32_t VertexAttributes::GlTypeToSize(GLenum type)
{
    switch (type) {
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_INT:
        return sizeof(GLint);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    default:
        LOG_WARNING("RETREVING SIZE OF UNEXPECTED TYPE!");
        return 0;
    }
}

uint32_t VertexAttributes::GetStride() const
{
    return _stride;
}
uint32_t VertexAttributes::GetLastOffset() const
{
    return _lastOffset;
}
