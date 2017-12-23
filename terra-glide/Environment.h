#pragma once

#include "Math.h"
#include <glm\trigonometric.hpp>
#include <glm\vec3.hpp>

class Environment
{
public:
    static constexpr float FarPlane = 500.0f;

    Environment() :
        m_horizontalSpeed(2),
        m_verticalSpeed(2),
        m_rotationSpeed(glm::radians(360.0f)),
        m_ambientStrength(0.2f),
        m_ambientColor({Math::color(255), Math::color(255), Math::color(255)})
    {}

    Environment(const Environment&) = default;
    ~Environment() = default;

    Environment& operator=(const Environment&) = default;

    float horizontalSpeed() const noexcept
    {
        return m_horizontalSpeed;
    }

    float verticalSpeed() const noexcept
    {
        return m_verticalSpeed;
    }

    float rotationSpeed() const noexcept
    {
        return m_rotationSpeed;
    }

    float ambientStrength() const noexcept
    {
        return m_ambientStrength;
    }

    const glm::vec3& ambientColor() const noexcept
    {
        return m_ambientColor;
    }

private:
    float m_horizontalSpeed;
    float m_verticalSpeed;
    float m_rotationSpeed;
    float m_ambientStrength;
    glm::vec3 m_ambientColor;
};
