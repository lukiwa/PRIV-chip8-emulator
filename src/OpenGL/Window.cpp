//
// Created by shaux on 13.08.2021.
//

#include "Window.h"
#include <functional>
#include <stdexcept>

namespace GLFW {

// needs to be a free function
void ResizeCallback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Constructs a new glfw windows and context
 * @param width window width
 * @param height window height
 * @param title window title
 * @param glfwContextMajorVersion OpenGL major version (default 3)
 * @param glfwContextMinorVersion OpenGL minor version (default 3)
 */
Window::Window(int width, int height, const char* title, int glfwContextMajorVersion, int glfwContextMinorVersion)
    : _windowHandle(nullptr)
    , _width(width)
    , _height(height)
    , _forceClose(false)

{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwContextMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwContextMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_windowHandle == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_windowHandle);
    glfwSetFramebufferSizeCallback(_windowHandle, ResizeCallback);
    glfwSetInputMode(_windowHandle, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
}

Window::~Window()
{
    glfwTerminate();
}

/**
 * Should window close
 * @return true if should close false otherwise
 */
bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(_windowHandle) || _forceClose;
}

/**
 * Force window close
 */
void Window::ForceClose()
{
    _forceClose = true;
}

/**
 * Swap buffers
 */
void Window::SwapBuffers() const
{
    glfwSwapBuffers(_windowHandle);
}

/**
 * Handle inputs to a program
 */
void Window::ProcessInput()
{
    glfwPollEvents();

    if (glfwGetKey(_windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_windowHandle, true);
    }
}
/**
 * Get window width
 * @return window width
 */
int Window::GetWidth() const
{
    return _width;
}

/**
 * Get window height
 * @return
 */
int Window::GetHeight() const
{
    return _height;
}

/**
 * Get GLFW window handle
 * @return glfw handle pointer
 */
GLFWwindow* Window::GetHandle()
{
    return _windowHandle;
}
}