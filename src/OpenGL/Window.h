#pragma once

#include <GLFW/glfw3.h>
namespace GLFW {
class Window {
public:
    Window(int width, int height, const char* title, int glfwContextMajorVersion = 3, int glfwContextMinorVersion = 3);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool ShouldClose() const;
    void ForceClose();
    void SwapBuffers() const;
    void ProcessInput();
    GLFWwindow* GetHandle();
    int GetWidth() const;
    int GetHeight() const;


private:
    GLFWwindow* _windowHandle;
    int _width;
    int _height;
    bool _forceClose;
};
}