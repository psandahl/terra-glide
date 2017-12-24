#pragma once

#include "Math.h"
#include <glm\trigonometric.hpp>
#include <glm\vec3.hpp>

class Environment
{
public:
    static constexpr float FarPlane = 500.0f;

    Environment() :
        m_terrainHeight(100.0f),
        m_horizontalSpeed(20),
        m_verticalSpeed(2),
        m_rotationSpeed(glm::radians(360.0f)),
        m_ambientStrength(0.2f),
        m_ambientColor({Math::color(255), Math::color(255), Math::color(255)}),
        m_sunDirection(glm::normalize(glm::vec3(-1, 0.3, 0))), // Yes, this is somewhat to the east.
        m_sunColor({Math::color(182), Math::color(126), Math::color(91)})
    {}

    Environment(const Environment&) = default;
    ~Environment() = default;

    Environment& operator=(const Environment&) = default;

    float terrainHeight() const noexcept
    {
        return m_terrainHeight;
    }

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

    const glm::vec3& sunDirection() const noexcept
    {
        return m_sunDirection;
    }

    const glm::vec3& sunColor() const noexcept
    {
        return m_sunColor;
    }

private:
    float m_terrainHeight;
    float m_horizontalSpeed;
    float m_verticalSpeed;
    float m_rotationSpeed;
    float m_ambientStrength;
    glm::vec3 m_ambientColor;
    glm::vec3 m_sunDirection;
    glm::vec3 m_sunColor;
};
