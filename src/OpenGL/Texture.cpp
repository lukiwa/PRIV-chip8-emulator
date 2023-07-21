#include "Texture.h"
#include "Tracing.h"

/**
 * Create new texture
 * @param textureType textureType type of texture (eg. GL_TEXTURE_2D)
 * @param dimensions dimension of the texture
 * @param pixelFormat pixel internal format (eg. GL_RGBA)
 * @param dataType pixel type (eg. GL_UNSIGNED_BYTE)
 * @param data texture data
 */
Texture::Texture(GLenum textureType, Dimensions dimensions, GLenum pixelFormat, GLenum dataType, const void* data)
    : _id(0)
    , _target(textureType)
    , _dimensions(dimensions)
    , _pixelFormat(pixelFormat)
    , _dataType(dataType)
{
    GlAssert(glGenTextures(1, &_id));
    GlAssert(glBindTexture(_target, _id));


    GLenum formatConverted = pixelFormat == GL_BGRA || GL_RGBA ? GL_RGBA : pixelFormat;

    switch (textureType) {
    case GL_TEXTURE_2D:
        GlAssert(glTexImage2D(
            GL_TEXTURE_2D, 0, formatConverted, _dimensions.x, _dimensions.y, 0, _pixelFormat, _dataType, data));
        break;
    case GL_TEXTURE_3D:
        GlAssert(glTexImage3D(GL_TEXTURE_3D, 0, formatConverted, _dimensions.x, _dimensions.y, _dimensions.z, 0,
            _pixelFormat, _dataType, data));
        break;
    default:
        LOG_ERROR("UNKNOWN TEXTURE TYPE!");
        break;
    }

}


/**
 * Destructs the texture and deletes it
 */
Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}

/**
 * Set texture parameters
 */
void Texture::SetTextureParameters() const
{
    GlAssert(glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GlAssert(glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GlAssert(glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GlAssert(glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

/**
 * Bind texture
 */
void Texture::Bind() const
{
    GlAssert(glBindTexture(_target, _id));
}

/**
 * Unbind texture
 */
void Texture::Unbind() const
{
    GlAssert(glBindTexture(_target, 0));
}

/**
 * Update subimage of the texture with data
 * @param pixels pixels buffer (empty for PBO)
 */
void Texture::SubImage(void* pixels) const
{
    if (_target == GL_TEXTURE_2D) {
        glTexSubImage2D(_target, 0, 0, 0, _dimensions.x, _dimensions.y, _pixelFormat, _dataType, pixels);
    } else {
        LOG_WARNING("Sub image of texture larger than 2D is not currently available");
    }
}
