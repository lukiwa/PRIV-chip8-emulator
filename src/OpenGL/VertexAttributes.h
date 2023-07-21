#pragma once

#include "GL/glew.h"
#include "IBoundable.h"
#include "Tracing.h"
#include <algorithm>
#include <cstdint>
#include <list>
#include <vector>

class VertexAttributes : public IBoundable {
public:
    VertexAttributes();
    ~VertexAttributes() = default;
    void Bind() const override;
    void Unbind() const override;

    void AddAttribute(uint32_t count, GLenum type);
    uint32_t GetStride() const;
    uint32_t GetLastOffset() const;

    static uint32_t GlTypeToSize(GLenum type);

private:
    struct VertexAttributeElement {
        uint32_t count;
        GLenum type;
        GLboolean normalized = GL_FALSE;
    };

    // I do not actually need to store it on the CPU side, but may be useful to debug
    std::vector<VertexAttributeElement> _attributes;
    mutable uint32_t _stride;
    mutable uint32_t _lastOffset;
};
