#include "PixelMapBuilder.h"

/**
 * Constructs new builder
 */
PixelMapBuilder::PixelMapBuilder()
    : _dimensions()
    , _internalPixelFormat(GL_RGBA)
    , _factory(nullptr)
{
}

/**
 * Set dimension of pixel map
 * @param dimensions
 * @return builder reference
 */
PixelMapBuilder& PixelMapBuilder::Size(Dimensions dimensions)
{
    _dimensions = dimensions;
    return *this;
}
/**
 * Selects pixel format
 * @param pixelFormat pixel format of the map
 * @return builder reference
 */
PixelMapBuilder& PixelMapBuilder::PixelFormat(int pixelFormat)
{
    _internalPixelFormat = pixelFormat;
    return *this;
}

/**
 * Selects factory for the internal components of the PixelMap
 * @param factory pixel map factory
 * @return builder refernce
 */
PixelMapBuilder& PixelMapBuilder::Factory(IPixelMapComponentsFactory* factory)
{
    _factory = factory;
    return *this;
}

/**
 * Constructs new PixelMap
 * @return pixel map unique_ptr
 */
std::unique_ptr<PixelMap> PixelMapBuilder::Build()
{
    return std::make_unique<PixelMap>(_dimensions, _internalPixelFormat, _factory);
}