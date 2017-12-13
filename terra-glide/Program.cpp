#include "Program.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <iterator>
#include <string>
#include <vector>

struct ShaderRequest2
{
    ShaderType shaderType;
    std::string filename;
    std::string filecontents;
};

std::optional<std::string> fromFile(const std::string& filename);

std::variant<std::string, std::shared_ptr<Program>>
makeProgram(const std::vector<ShaderRequest>& requests)
{
    std::vector<ShaderRequest2> requests2;
    for (auto& request : requests)
    {
        auto result = fromFile(request.filename);
        if (result.has_value())
        {
            requests2.push_back( {request.shaderType, request.filename, result.value()} );
        }
        else
        {
            return { "Can't open file " + request.filename };
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