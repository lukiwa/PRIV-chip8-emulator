#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

#ifndef WSL1
#define ALLOW_DISPLAY
#else
#define ALLOW_DISPLAY setenv("DISPLAY", "127.0.0.1:0", true)
#endif

#ifndef DEBUG
#define LOG(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_WARNING(fmt, ...)
#define GlAssert(code) code;

#else
//ORDINARY LOG
#define LOG(fmt, ...)                             \
    do {                                          \
        fprintf(stderr, fmt "\n", ##__VA_ARGS__); \
        fflush(stderr);                           \
    } while (0)

//WARNING LOG
#define LOG_WARNING(fmt, ...)                                                                                                         \
    do {                                                                                                                              \
        fprintf(stderr, "\033[0;33mWARNING at [%s:%s:%d]: " fmt "\033[0m\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__); \
        fflush(stderr);                                                                                                               \
    } while (0)

//ERROR LOG
#define LOG_ERROR(fmt, ...)                                                                                                         \
    do {                                                                                                                            \
        fprintf(stderr, "\033[0;31mERROR at [%s:%s:%d]: " fmt "\033[0m\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__); \
        fflush(stderr);                                                                                                             \
    } while (0)

//OPENGL LOGS
#define LOG_OPENGL_ERROR(code, error, filename, linenumber)                                                             \
    do {                                                                                                                \
        fprintf(stderr, "\033[0;35mOpenGL ERROR: [%s] in [%s] at [%s:%d]\033[0m\n", error, code, filename, linenumber); \
        fflush(stderr);                                                                                                 \
    } while (0)

static const char* GLErrorToString(GLenum const error)
{
    switch (error) {
    // opengl 2 errors (8)
    case GL_NO_ERROR:
        return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";

    case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";

        // opengl 3 errors (1)
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";

        // gles 2, 3 and gl 4 error are handled by the switch above
    default:
        return "Unknown error";
    }
}

inline static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR) {
    }
}

inline static void GLCheckError(const char* code, const char* filename, uint32_t lineNumber)
{
    uint32_t errorCount = 0;
    while (GLenum error = glGetError()) {
        LOG_OPENGL_ERROR(code, GLErrorToString(error), filename, lineNumber);
        ++errorCount;
    }
    if (errorCount > 0) {
        abort();
    }
}

#define GlAssert(code)                           \
    do {                                         \
        GLClearError();                          \
        code;                                    \
        GLCheckError(#code, __FILE__, __LINE__); \
    } while (0)

#endif