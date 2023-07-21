#pragma once
#include "string"
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram() = default;
    ShaderProgram(const ShaderProgram& other);
    ShaderProgram& operator=(const ShaderProgram& other);
    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    ~ShaderProgram();
    void Use() const;

    void Delete() const;

private:
    GLuint _programId;
    friend class ShaderProgramBuilder;
};

class ShaderProgramBuilder {
public:
    ShaderProgramBuilder();
    ~ShaderProgramBuilder() = default;

    ShaderProgramBuilder& ShadersRoot(const std::string& root);
    ShaderProgramBuilder& ShaderFilename(GLuint type, const std::string& shaderFilename);
    ShaderProgramBuilder& CreateProgram();
    ShaderProgramBuilder& CompileShader(GLuint type);
    ShaderProgramBuilder& LinkShaders();
    ShaderProgramBuilder& Validate(int& outResult);
    ShaderProgram Build() const;

    const std::string& GetShaderSource(GLuint type) const;
    GLuint GetProgramId() const;
    GLuint GetShaderId(GLuint type) const;

private:
    static std::string FileToString(const std::string& filepath);

    std::string _shadersRoot;
    GLuint _programId;
    GLuint _vertexShaderId;
    GLuint _fragmentShaderId;
    std::string _vertexShaderSource;
    std::string _fragmentShaderSource;
};
