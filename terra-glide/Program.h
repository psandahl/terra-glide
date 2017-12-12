#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

enum class ShaderType
{
    Fragment = 0,
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

};