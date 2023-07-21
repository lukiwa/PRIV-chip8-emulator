#include "OpenGL/Engine.h"
#include "Utilities/Tracing.h"
#include <iostream>
#include <memory>

#include "OpenGL/PixelMapBuilder.h"
#include "OpenGL/Window.h"
#include "Utilities/Random.h"

int main(int argc, char** argv)
{
    Random::Seed();

    // window
    ALLOW_DISPLAY;
    GLFW::Window window(128, 128, "Chip8");

    // Glew
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize OpenGL loader!");
    }

    // Drawing engine
    Engine drawingEngine;
    auto renderer = drawingEngine.Init();

    // PixelMap
    PixelMapBuilder pixelMapBuilder;
    std::unique_ptr<PixelMapComponentsFactory> componentsFactory(new PixelMapComponentsFactory());
    pixelMapBuilder.Factory(componentsFactory.get()).PixelFormat(GL_RGBA);
    pixelMapBuilder.Size({ 128, 128, 0 });
    auto pixelMap = pixelMapBuilder.Build();
    renderer->SetPixelMap(pixelMap.get());


    while (!window.ShouldClose()) {
        window.ProcessInput();
        for (int x = 0; x < 128; ++x) {
            for (int y = 0; y < 128; ++y) {
                pixelMap->SetPixel(x, y, { Random::Int(0, 255), Random::Int(0, 255), Random::Int(0, 255), 255 });
            }
        }
        renderer->Draw();
        window.SwapBuffers();
    }

    return 0;
}
