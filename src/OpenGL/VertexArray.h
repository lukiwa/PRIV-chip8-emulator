#pragma once
#include "IBoundable.h"
#include <GL/glew.h>

class VertexArray : public IBoundable {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const override;
    void Unbind() const override;

private:
    GLuint _id;
};