#pragma once
#include "IBoundable.h"
#include <GL/glew.h>

class VertexBuffer : public IBoundable {
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

private:
    GLuint _id;
};
