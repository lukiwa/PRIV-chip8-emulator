#pragma once
#include "PixelMap.h"

class PixelMapBuilder {
public:
    PixelMapBuilder();
    ~PixelMapBuilder() = default;

    PixelMapBuilder& Size(Dimensions dimensions);
    PixelMapBuilder& PixelFormat(int pixelFormat);
    PixelMapBuilder& Factory(IPixelMapComponentsFactory* factory);
    std::unique_ptr<PixelMap> Build();

private:
    Dimensions _dimensions;
    int _internalPixelFormat;
    IPixelMapComponentsFactory* _factory;
};
