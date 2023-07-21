#pragma once

class IBoundable {
public:
    virtual ~IBoundable() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};