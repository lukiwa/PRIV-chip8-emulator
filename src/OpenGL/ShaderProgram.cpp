#include "ShaderProgram.h"
#include "Tracing.h"
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Constructors
 *
 */
ShaderProgram::ShaderProgram(const ShaderProgram& other)
{
    _programId = other._programId;
}
ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other)
{
    if (this == &other) {
        return *this;
    }

    _programId = other._programId;
    return *this;
}
ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
    _programId = other._programId;
    other._programId = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this == &other) {
        return *this;
    }

    _programId = other._programId;
    other._programId = 0;
    return *this;
}
ShaderProgram::~ShaderProgram()
{
    Delete();
}

/**
 * Use program
 */
void ShaderProgram::Use() const
{
    GlAssert(glUseProgram(_programId));
}

/**
 * Delete program
 */
void ShaderProgram::Delete() const
{
    GlAssert(glDeleteProgram(_programId));
}

ShaderProgramBuilder::ShaderProgramBuilder()
    : _shadersRoot("../../src/OpenGL/shaders/")
    , _programId(0)
    , _vertexShaderId(0)
    , _fragmentShaderId(0)
{
}

/**
 * Change default shaders root (default: src/OpenGL/shaders/)
 * @param root new root
 * @return "this" reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::ShadersRoot(const std::string& root)
{
    _shadersRoot = root;
    return *this;
}

/**
 * Read shaders source from filename inside _shadersRoot directory
 * @param type type of the shader
 * @param shaderFilename filename of the shader
 * @return "this" reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::ShaderFilename(GLuint type, const std::string& shaderFilename)
{
    switch (type) {
    case GL_VERTEX_SHADER:
        _vertexShaderSource = FileToString(_shadersRoot + shaderFilename);
        break;
    case GL_FRAGMENT_SHADER:
        _fragmentShaderSource = FileToString(_shadersRoot + shaderFilename);
        break;
    default:
        LOG_ERROR("SHADER TYPE NOT RECOGNIZED");
    }
    return *this;
}

/**
 * Create shader program
 * @return this reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::CreateProgram()
{
    _programId = glCreateProgram();
    return *this;
}

/**
 * Compile single shader
 * @param type type of the shader to be compiled
 * @param source source code of th shader
 * @return this reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::CompileShader(GLuint type)
{
    GLuint id = glCreateShader(type);
    const char* src_c_str = type == GL_VERTEX_SHADER ? _vertexShaderSource.c_str() : _fragmentShaderSource.c_str();
    GlAssert(glShaderSource(id, 1, &src_c_str, nullptr));
    GlAssert(glCompileShader(id));

    int result;
    GlAssert(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        char message[1024];

        GlAssert(glGetShaderInfoLog(id, sizeof(message), nullptr, message));
        LOG_ERROR("FAILED TO COMPILE SHADER OF TYPE: %d. MESSAGE: \n %s \n", type, message);
        GlAssert(glDeleteShader(id));
        id = 0;
    }

    if (type == GL_VERTEX_SHADER) {
        _vertexShaderId = id;
    } else {
        _fragmentShaderId = id;
    }
    return *this;
}

/**
 * Link programs.
 * @return "this" reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::LinkShaders()
{
    GlAssert(glAttachShader(_programId, _vertexShaderId));
    GlAssert(glAttachShader(_programId, _fragmentShaderId));
    GlAssert(glLinkProgram(_programId));
    GlAssert(glDeleteShader(_vertexShaderId));
    GlAssert(glDeleteShader(_fragmentShaderId));

    return *this;
}

/**
 * Validate linked program proper error message will be displayed on error/
 * @return this reference
 */
ShaderProgramBuilder& ShaderProgramBuilder::Validate(int& outResult)
{
    GlAssert(glGetProgramiv(_programId, GL_LINK_STATUS, &outResult));
    if (outResult == GL_FALSE) {
        char message[512];
        GlAssert(glGetProgramInfoLog(_programId, sizeof(message), nullptr, message));
        LOG_ERROR("FAILED TO LINK SHADERS TO PROGRAM. MESSAGE: \n %s \n", message);
    }

    return *this;
}

/**
 * Build program
 * @return builded program
 */
ShaderProgram ShaderProgramBuilder::Build() const
{
    ShaderProgram program;
    program._programId = _programId;
    program.Use();

    return program;
}

/**
 * Get shader source of type
 * @param type type of shader
 * @return shader source
 */
const std::string& ShaderProgramBuilder::GetShaderSource(GLuint type) const
{
    switch (type) {
    case GL_VERTEX_SHADER:
        return _vertexShaderSource;
    case GL_FRAGMENT_SHADER:
        return _fragmentShaderSource;
    default:
        LOG_ERROR("SHADER TYPE NOT RECOGNIZED");
        return _vertexShaderSource;
    }
}

/**
 * Read content of filepath and store return as string
 * @param filepath path to file
 * @return read content
 */
std::string ShaderProgramBuilder::FileToString(const std::string& filepath)
{
    {
        std::ifstream file(filepath);
        std::ostringstream oss;
        if (file.is_open()) {
            oss << file.rdbuf();
        } else {
            LOG_ERROR("ERROR OPENING FILE");
        }
        return oss.str();
    }
}
/**
 * Get id of the program (0 on error)
 * @return program id
 */
GLuint ShaderProgramBuilder::GetProgramId() const
{
    return _programId;
}

/**
 * Get id of the shader
 * @param type shader type
 * @return shader ID
 */
GLuint ShaderProgramBuilder::GetShaderId(GLuint type) const
{
    switch (type) {
    case GL_VERTEX_SHADER:
        return _vertexShaderId;
    case GL_FRAGMENT_SHADER:
        return _fragmentShaderId;
    default:
        LOG_ERROR("SHADER TYPE NOT RECOGNIZED");
        return 0;
    }
}
