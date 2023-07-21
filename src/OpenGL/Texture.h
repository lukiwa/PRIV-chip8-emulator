#pragma once
#include "Dimensions.h"
#include "IBoundable.h"
#include <GL/glew.h>
#include <memory>

class ITexture : public IBoundable {
public:
    virtual ~ITexture() = default;
    virtual void SetTextureParameters() const = 0;
    virtual void SubImage(void* pixels) const = 0;
};

class Texture : public ITexture {
public:
    Texture(GLenum textureType, Dimensions dimensions, GLenum pixelFormat, GLenum dataType, const void* data);

    ~Texture();
    void SetTextureParameters() const override;
    void SubImage(void* pixels) const override;

    void Bind() const override;
    void Unbind() const override;

private:
    GLuint _id;

    GLenum _target;
    Dimensions _dimensions;
    GLenum _pixelFormat;
    GLenum _dataType;
};