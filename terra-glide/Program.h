#pragma once

#include <glad\glad.h>
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
    ~Program() { std::cerr << "Die!";  }

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
private:
    GLuint m_program;
};