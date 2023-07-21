#include "ShaderProgram.h"
#include "Tracing.h"
#include "Window.h"
#include "gtest/gtest.h"

class ShaderProgramTestFixture : public ::testing::Test {
public:
    ShaderProgramTestFixture()
    {
    }

    void SetUp() override
    {
        //needed to set current context
        ALLOW_DISPLAY;

        ASSERT_NO_THROW(_window.reset(new GLFW::Window(10, 10, "Test")));
        ASSERT_EQ(glewInit(), GLEW_OK);


        _shaderProgramBuilder.ShadersRoot("../../test/OpenGL/shaders/");
    }

    void TearDown() override
    {
        _window.reset(nullptr);
    }

    ShaderProgramBuilder _shaderProgramBuilder;
    std::unique_ptr<GLFW::Window> _window;
};

TEST_F(ShaderProgramTestFixture, ShaderProgramSucesfullyReadsShadersFileToString)
{
    _shaderProgramBuilder.ShaderFilename(GL_FRAGMENT_SHADER, "fragment_shader_test.glsl");
    auto source = _shaderProgramBuilder.GetShaderSource(GL_FRAGMENT_SHADER);
    std::istringstream iss(source);
    std::string firstLine;
    iss >> firstLine;

    ASSERT_STREQ("//fragment_shader_test", firstLine.c_str());

    _shaderProgramBuilder.ShaderFilename(GL_VERTEX_SHADER, "vertex_shader_test.glsl");
    source = _shaderProgramBuilder.GetShaderSource(GL_VERTEX_SHADER);
    iss.str(source);
    firstLine.clear();
    iss >> firstLine;

    ASSERT_STREQ("//vertex_shader_test", firstLine.c_str());
}

TEST_F(ShaderProgramTestFixture, CompileShadersMakeIdsNotZero)
{
    _shaderProgramBuilder.ShaderFilename(GL_VERTEX_SHADER, "vertex_shader_test.glsl")
        .ShaderFilename(GL_FRAGMENT_SHADER, "fragment_shader_test.glsl")
        .CreateProgram();
    ASSERT_STRNE(_shaderProgramBuilder.GetShaderSource(GL_VERTEX_SHADER).c_str(), "");
    ASSERT_STRNE(_shaderProgramBuilder.GetShaderSource(GL_FRAGMENT_SHADER).c_str(), "");

    _shaderProgramBuilder.CompileShader(GL_VERTEX_SHADER);
    _shaderProgramBuilder.CompileShader(GL_FRAGMENT_SHADER);

    ASSERT_NE(_shaderProgramBuilder.GetProgramId(), 0);
    ASSERT_NE(_shaderProgramBuilder.GetShaderId(GL_VERTEX_SHADER), 0);
    ASSERT_NE(_shaderProgramBuilder.GetShaderId(GL_FRAGMENT_SHADER), 0);
}

TEST_F(ShaderProgramTestFixture, ValidateLinkingIsNotGlFalse)
{
    _shaderProgramBuilder.ShaderFilename(GL_VERTEX_SHADER, "vertex_shader_test.glsl")
        .ShaderFilename(GL_FRAGMENT_SHADER, "fragment_shader_test.glsl")
        .CreateProgram();
    ASSERT_STRNE(_shaderProgramBuilder.GetShaderSource(GL_VERTEX_SHADER).c_str(), "");
    ASSERT_STRNE(_shaderProgramBuilder.GetShaderSource(GL_FRAGMENT_SHADER).c_str(), "");

    _shaderProgramBuilder.CompileShader(GL_VERTEX_SHADER);
    _shaderProgramBuilder.CompileShader(GL_FRAGMENT_SHADER);

    ASSERT_NE(_shaderProgramBuilder.GetProgramId(), 0);
    ASSERT_NE(_shaderProgramBuilder.GetShaderId(GL_VERTEX_SHADER), 0);
    ASSERT_NE(_shaderProgramBuilder.GetShaderId(GL_FRAGMENT_SHADER), 0);

    int validationResult = 0;
    _shaderProgramBuilder.LinkShaders().Validate(validationResult);

    ASSERT_NE(validationResult, GL_FALSE);
}
