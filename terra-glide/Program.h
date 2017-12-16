#pragma once

#include <glad\glad.h>
#include <glm\vec3.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

enum class ShaderType
{
    Fragment,
    Vertex
};

struct ShaderRequest
{
    ShaderType shaderType;
    std::string filename;
};

class Program;

std::variant<std::string, std::shared_ptr<Program>> 
makeProgram(const std::vector<ShaderRequest>& requests);

class Program
{
public:
    Program() = delete;
    Program(GLuint program):
        m_program(program)
    {}
    Program(const Program&) = default;
    ~Program() = default;

    Program& operator=(const Program&) = default;

    void enable() const noexcept
    {
        glUseProgram(m_program);
    }

    void disable() const noexcept
    {
        glUseProgram(0);
    }

    void release() noexcept
    {
        if (m_program != 0)
        {
            glDeleteProgram(m_program);
            m_program = 0;
        }
    }

    void setUniform(const std::string& name, const glm::vec3& vec) const noexcept
    {
        auto loc = glGetUniformLocation(m_program, name.c_str());
        glUniform3fv(loc, 1, glm::value_ptr(vec));
    }

private:
    GLuint m_program;
};