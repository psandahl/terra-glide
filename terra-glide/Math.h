#pragma once

#include <glm\mat3x3.hpp>
#include <glm\mat4x4.hpp>

class Math
{
public:
    static glm::mat3 normalMatrix(const glm::mat4& mat) noexcept
    {
        return glm::mat3(glm::transpose(glm::inverse(mat)));
    }
};
