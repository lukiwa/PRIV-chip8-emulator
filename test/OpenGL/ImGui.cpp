#include "ImGuiHandler.h"
#include "Tracing.h"
#include "Window.h"
#include "gtest/gtest.h"
#include <GL/glew.h>

class ImGuiTestFixture : public ::testing::Test {
public:
    void SetUp() override
    {
        ALLOW_DISPLAY;

        ASSERT_NO_THROW(_window.reset(new GLFW::Window(10, 10, "Test")));
        ASSERT_EQ(glewInit(), GLEW_OK);
    }

    void TearDown() override
    {
        _window.reset(nullptr);
    }

    std::unique_ptr<GLFW::Window> _window;
};

TEST_F(ImGuiTestFixture, ImGuiInitShouldSucceedAfterInitalizingWindowAndGlew)
{
    IMGUI_CHECKVERSION();

    auto context = ImGui::CreateContext();
    ASSERT_NE(context, nullptr);

    ASSERT_EQ(ImGui_ImplGlfw_InitForOpenGL(_window->GetHandle(), false), true);

    std::string version = "#version 130";
    ASSERT_EQ(ImGui_ImplOpenGL3_Init(version.c_str()), true);
}