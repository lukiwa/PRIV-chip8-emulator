#include "Engine.h"
/**
 * Constructs new engine and initialize OpenGL elements
 */
Engine::Engine()
    : _vao()
    , _vertexBuffer(_positions, sizeof(_positions))
    , _indexBuffer(_indices, 6)
    , _attributes()
    , _program()
{
}
/**
 * Initialize engine
 * @return created renderer
 */
std::unique_ptr<Renderer> Engine::Init()
{
    _vertexBuffer.Bind();
    _attributes.AddAttribute(2, GL_FLOAT); // positions
    _attributes.AddAttribute(2, GL_FLOAT); // texture coordinates
    _attributes.Bind();

    ShaderProgramBuilder builder;
    int validationResult = 0;
    _program = builder.ShaderFilename(GL_VERTEX_SHADER, "vertex_shader.glsl")
                   .ShaderFilename(GL_FRAGMENT_SHADER, "fragment_shader.glsl")
                   .CreateProgram()
                   .CompileShader(GL_VERTEX_SHADER)
                   .CompileShader(GL_FRAGMENT_SHADER)
                   .LinkShaders()
                   .Validate(validationResult)
                   .Build();

    return std::make_unique<Renderer>(_vao, _indexBuffer, _program);
}
