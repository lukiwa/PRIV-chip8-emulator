#include "PixelMap.h"
#include "PixelBufferObject.h"
#include "Texture.h"
#include "Tracing.h"
#include "Window.h"
#include "gtest/gtest.h"
#include <memory>

class MockPixelBufferObject : public IPixelBufferObject {
public:
    MockPixelBufferObject(int width, int height, int internalFormat)
    {
        _buffer.resize(width * height * internalFormat);
    }
    void Bind() const override
    {
        // UNUSED
    }
    void Unbind() const override
    {
        // UNUSED
    }
    void* MapBuffer() const override
    {
        return (void*)(_buffer.data());
    }
    void UnmapBuffer() const override
    {
        _buffer.clear();
    }

private:
    mutable std::vector<GLubyte> _buffer;
};

class MockTexture : public ITexture {
public:
    void Bind() const override
    {
        // UNUSED
    }
    void Unbind() const override
    {
        // UNUSED
    }
    void SetTextureParameters() const override
    {
        // UNUSED
    }
    void SubImage(void*) const override
    {
        // UNUSED
    }
};

class MockComponentFactory : public IPixelMapComponentsFactory {
public:
    Components CreateComponents(Dimensions dimensions, int internalPixelFormat, GLenum, const void*) const override
    {
        std::unique_ptr<IPixelBufferObject> pbo(
            new MockPixelBufferObject(dimensions.x, dimensions.y, internalPixelFormat));
        std::unique_ptr<ITexture> texture(new MockTexture());
        texture->SetTextureParameters();
        return { std::move(pbo), std::move(texture) };
    }
};

class PixelMapTestFixture : public ::testing::Test {
public:
    PixelMapTestFixture()
        : _width(255)
        , _height(255)
        , _pixelFormat(GL_RGBA)
        , _window(nullptr)
        , _pixelMap(nullptr)
    {
    }

    void SetUp() override
    {
        ALLOW_DISPLAY;
        ASSERT_NO_THROW(_window.reset(new GLFW::Window(10, 10, "Test")));
        ASSERT_EQ(glewInit(), GLEW_OK);

        _componentsFactory = std::make_unique<PixelMapComponentsFactory>();
        _pixelMap
            = std::make_unique<PixelMap>(Dimensions{ _width, _height, 0 }, _pixelFormat, _componentsFactory.get());
        _pixelMap->Clear();
    }

    void TearDown() override
    {
        _pixelMap.reset(nullptr);
        _componentsFactory.reset(nullptr);
        _window.reset(nullptr);
    }

    int _width;
    int _height;
    int _pixelFormat;
    std::unique_ptr<GLFW::Window> _window;
    std::unique_ptr<PixelMap> _pixelMap;
    std::unique_ptr<PixelMapComponentsFactory> _componentsFactory;
};

TEST_F(PixelMapTestFixture, RealImplementationReturnsNonNullptrMappedBuffer)
{
    PixelBufferObject pbo(_width, _height, _pixelFormat);
    pbo.Bind();
    ASSERT_NE(pbo.MapBuffer(), nullptr);
}

TEST_F(PixelMapTestFixture, PixelInternalFormatMatchesRGBA)
{
    const int pixelFormatNumber = PixelBufferObject::ConvertFormatToNumber(_pixelFormat);

    _pixelMap->SetPixel(1, 1, { 255, 255, 255, 255 });
    auto pixel = _pixelMap->GetPixel(1, 1);

    ASSERT_EQ(pixel.size(), pixelFormatNumber);
}

TEST_F(PixelMapTestFixture, PixelComponentsMatches)
{
    const int pixelFormatNumber = PixelBufferObject::ConvertFormatToNumber(_pixelFormat);

    _pixelMap->SetPixel(1, 1, { 100, 100, 100, 100 });
    auto pixel = _pixelMap->GetPixel(1, 1);

    ASSERT_EQ(pixel.size(), pixelFormatNumber);
    for (const auto& component : pixel) {
        ASSERT_EQ(component, 100);
    }
}

TEST_F(PixelMapTestFixture, PixelsChangeOnlyOnGivenRange)
{
    const int widthRangeToChange = _width / 2;
    const int heightRangeToChange = _height / 2;

    for (int x = 0; x < widthRangeToChange; ++x) {
        for (int y = 0; y < heightRangeToChange; ++y) {
            _pixelMap->SetPixel(x, y, { 100, 100, 100, 100 });

            auto pixel = _pixelMap->GetPixel(x, y);
            for (const auto& component : pixel) {
                ASSERT_EQ(component, 100);
            }
        }
    }

    for (int x = widthRangeToChange; x < _width; ++x) {
        for (int y = heightRangeToChange; y < _height; ++y) {
            auto pixel = _pixelMap->GetPixel(x, y);
            for (const auto& component : pixel) {
                ASSERT_EQ(component, 255);
            }
        }
    }
}
