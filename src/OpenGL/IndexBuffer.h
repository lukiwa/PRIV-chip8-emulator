#pragma once
#include <GL/glew.h>
#include "IBoundable.h"

class IndexBuffer : public IBoundable{
public:
    IndexBuffer(const GLuint* data, uint32_t count);
    ~IndexBuffer();

    void Bind() const override;
    void Unbind() const override;
    inline uint32_t Count() const
    {
        return _count;
    }

private:
    GLuint _id;
    uint32_t _count;
};
