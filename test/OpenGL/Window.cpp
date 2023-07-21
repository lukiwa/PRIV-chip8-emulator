#include <GL/glew.h>
#include "Window.h"
#include "gtest/gtest.h"
#include "Tracing.h"


TEST(WindowTests, WindowShouldNoThrow)
{
    ALLOW_DISPLAY;
    ASSERT_NO_THROW(GLFW::Window window(10, 10, "Test"));
}

TEST(WindowTests, GlewInitShouldSucceedAfterWindowCreation)
{
    ALLOW_DISPLAY;
    GLFW::Window window(10, 10, "Test");
    ASSERT_EQ(glewInit(), GLEW_OK);
}

