#include "Program.h"
#include <glad\glad.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <iterator>
#include <string>
#include <variant>
#include <vector>

struct ShaderRequest2
{
    ShaderType shaderType;
    std::string filename;
    std::string filecontents;
};

std::optional<std::string> fromFile(const std::string& filename);
GLenum fromShaderType(ShaderType shaderType);
std::variant<std::string, GLuint> compileShader(const ShaderRequest2& request);

std::variant<std::string, std::shared_ptr<Program>>
makeProgram(const std::vector<ShaderRequest>& requests)
{
    std::vector<ShaderRequest2> requests2;
    for (auto& request : requests)
    {
        auto result = fromFile(request.filename);
        if (result.has_value())
        {
            requests2.push_back( { request.shaderType, request.filename, result.value() } );
        }
        else
        {
            return { "Can't open file " + request.filename };
        }
    }

    std::vector<GLuint> shaders;
    for (auto& request : requests2)
    {
        auto result = compileShader(request);
        if (std::holds_alternative<GLuint>(result))
        {
            shaders.push_back(std::get<1>(result));
        }
        else
        {
            return { request.filename + ": " + std::get<0>(result) }; 
        }
    }

    auto retval("Bad horsie");
    return retval;
}

std::optional<std::string> fromFile(const std::string& filename)
{
    std::ifstream infile(filename);
    if (infile.is_open())
    {
        auto contents = std::string(std::istreambuf_iterator<char>(infile),
                                    std::istreambuf_iterator<char>());
        return { contents };
    }
    else
    {
        return {};
    }
}

GLenum fromShaderType(ShaderType shaderType)
{
    switch (shaderType)
    {
    case ShaderType::Fragment:
        return GL_FRAGMENT_SHADER;
    case ShaderType::Vertex:
        return GL_VERTEX_SHADER;
    default:
        std::cerr << "Error: Impossible ShaderType value.\n" << std::endl;
        return 0;
    }
}

std::variant<std::string, GLuint> compileShader(const ShaderRequest2& request)
{
    auto shader = glCreateShader(fromShaderType(request.shaderType));
    const GLchar* src[1];
    src[0] = request.filecontents.c_str();
    glShaderSource(shader, 1, src, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
    {
        return { shader };
    }
    else
    {
        GLchar infoLog[500];
        glGetShaderInfoLog(shader, 500, nullptr, infoLog);
        return { infoLog };
    }
}