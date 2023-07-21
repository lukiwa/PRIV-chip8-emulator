#pragma once

#include "Tracing.h"
#include "IndexBuffer.h"
#include "PixelMap.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include <vector>

class Renderer {
public:
    Renderer(VertexArray& vao, IndexBuffer& ibo, ShaderProgram& program);
    ~Renderer() = default;

    void Draw() const;

    void SetPixelMap(PixelMap* pixelMap);

    void ClearColor(const std::vector<int>& components) const;

    void Clear() const;

private:
    VertexArray& _vao;
    IndexBuffer& _ibo;
    ShaderProgram& _program;
    PixelMap* _pixelMap;
};
