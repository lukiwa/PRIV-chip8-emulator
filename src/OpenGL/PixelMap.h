#pragma once
#include "Dimensions.h"
#include "IBoundable.h"
#include "PixelBufferObject.h"
#include "Texture.h"
#include <cassert>
#include <vector>

class IPixelMapComponentsFactory {
public:
    using Components = std::pair<std::unique_ptr<IPixelBufferObject>, std::unique_ptr<ITexture>>;
    virtual ~IPixelMapComponentsFactory() = default;
    virtual Components CreateComponents(
        Dimensions dimensions, int internalPixelFormat, GLenum dataType, const void* data) const = 0;
};

class PixelMapComponentsFactory : public IPixelMapComponentsFactory {
public:
    virtual Components CreateComponents(
        Dimensions dimensions, int internalPixelFormat, GLenum dataType, const void* data) const override
    {
        std::unique_ptr<IPixelBufferObject> pbo(new PixelBufferObject(dimensions.x, dimensions.y, internalPixelFormat));
        std::unique_ptr<ITexture> texture(new Texture(
            dimensions.z == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, dimensions, internalPixelFormat, dataType, data));
        texture->SetTextureParameters();
        pbo->Unbind();
        return { std::move(pbo), std::move(texture) };
    }
};

class IPixelMap {
public:
    virtual ~IPixelMap() = default;
    virtual void SetBuffer(const std::vector<GLubyte>& buffer) = 0;
    virtual void SetAllPixels(const std::vector<int>& components) = 0;
    virtual void SetPixel(int x, int y, const std::vector<int>& components) = 0;
    virtual std::vector<GLubyte> GetPixel(int x, int y) const = 0;
    virtual void SwapBuffer() = 0;
    virtual void Clear() = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};

class PixelMap : public IBoundable, public IPixelMap {
public:
    void Bind() const override;
    void Unbind() const override;

    PixelMap(Dimensions dimensions, int internalPixelFormat, IPixelMapComponentsFactory* factory);
    ~PixelMap() = default;

    void SetAllPixels(const std::vector<int>& components) override;
    void SetBuffer(const std::vector<GLubyte>& buffer) override;
    void SetPixel(int x, int y, const std::vector<int>& components) override;
    std::vector<GLubyte> GetPixel(int x, int y) const override;
    void SwapBuffer() override;
    void Clear() override;
    int GetWidth() const override;
    int GetHeight() const override;

private:
    int _pixelType;
    int _width;
    int _height;

    std::unique_ptr<IPixelBufferObject> _pbo;
    std::unique_ptr<ITexture> _texture;
    std::vector<GLubyte> _pixelBuffer;
};
