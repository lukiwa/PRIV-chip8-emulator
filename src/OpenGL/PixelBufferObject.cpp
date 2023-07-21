#include "PixelBufferObject.h"

#include "Tracing.h"

/**
 * Create new pixel buffer object
 * @param width how many pixel columns
 * @param height how many pixel row
 * @param internalFormat format of pixels (eg. GL_RGBA)
 */
PixelBufferObject::PixelBufferObject(int width, int height, int internalFormat)
    : _id(0)
{
    GlAssert(glGenBuffers(1, &_id));
    GlAssert(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _id));
    GlAssert(glBufferData(
        GL_PIXEL_UNPACK_BUFFER, width * height * ConvertFormatToNumber(internalFormat), nullptr, GL_STREAM_DRAW));
}

PixelBufferObject::~PixelBufferObject()
{
    GlAssert(glDeleteBuffers(1, &_id));
}

/**
 * Convert internal pixel format to number of pixel components (eg. GL_RGBA -> 4)
 * @param internalFormat pixel format
 * @return number of components
 */
int PixelBufferObject::ConvertFormatToNumber(int internalFormat)
{
    switch (internalFormat) {
    case GL_RGBA:
    case GL_BGRA:
        return 4;
    case GL_RGB:
        return 3;
    default:
        LOG_WARNING("Format not found!");
        return 0;
    }
}
/**
 * Bind PBO
 */
void PixelBufferObject::Bind() const
{
    GlAssert(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, _id));
}

/**
 * Unbind PBO
 */
void PixelBufferObject::Unbind() const
{
    GlAssert(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
}

/**
 * Map buffer
 * @return mapped buffer ready to be written to
 */
void* PixelBufferObject::MapBuffer() const
{
    return glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
}

/**
 * Unmap buffer
 */
void PixelBufferObject::UnmapBuffer() const
{
    GlAssert(glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER));
}
