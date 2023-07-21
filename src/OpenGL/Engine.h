#pragma once
#include "Renderer.h"
#include "VertexAttributes.h"
#include "VertexBuffer.h"
#include <memory>

class Engine {
public:
    Engine();
    ~Engine() = default;

    std::unique_ptr<Renderer> Init();

private:
    GLfloat _positions[16] = {
        1.0, 1.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f, 1.0f // top left
    };

    GLuint _indices[6] = {
        0, 1, 3, // first  triangle
        1, 2, 3 // second triangle
    };

    VertexArray _vao;
    VertexBuffer _vertexBuffer;
    IndexBuffer _indexBuffer;
    VertexAttributes _attributes;
    ShaderProgram _program;
};
