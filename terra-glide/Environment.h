#pragma once

#include <glm\trigonometric.hpp>

class Environment
{
public:
    Environment():
        m_horizontalSpeed(2),
        m_verticalSpeed(2),
        m_rotationSpeed(glm::radians(360.0f))
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

private:
    float m_horizontalSpeed;
    float m_verticalSpeed;
    float m_rotationSpeed;
};
