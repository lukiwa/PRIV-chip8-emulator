#pragma once
#include "IBoundable.h"
#include <GL/glew.h>

class IPixelBufferObject : public IBoundable {
public:
    virtual ~IPixelBufferObject() = default;
    virtual void* MapBuffer() const = 0;
    virtual void UnmapBuffer() const = 0;
};

class PixelBufferObject : public IPixelBufferObject {

public:
    PixelBufferObject(int width, int height, int internalFormat);
    ~PixelBufferObject();

    void Bind() const override;
    void Unbind() const override;

    void* MapBuffer() const override;
    void UnmapBuffer() const override;

    static int ConvertFormatToNumber(int internalFormat);

private:
    GLuint _id;
};
