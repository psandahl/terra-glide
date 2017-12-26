#pragma once

#include "Math.h"
#include <glm\trigonometric.hpp>
#include <glm\vec3.hpp>

class Environment
{
public:
    static constexpr float FarPlane = 850.0f;

    Environment() :
        m_terrainHeight(200.0f),
        m_horizontalSpeed(20),
        m_verticalSpeed(2),
        m_rotationSpeed(glm::radians(360.0f)),
        m_ambientStrength(0.2f),
        m_ambientColor({ Math::color(255), Math::color(255), Math::color(255) }),
        m_sunDirection(glm::normalize(glm::vec3(-1, 0.3, 0))), // Yes, this is somewhat to the east.
        m_sunColor({ Math::color(182), Math::color(126), Math::color(91) }),
        m_skyColor({ Math::color(70), Math::color(106), Math::color(200) }),
        m_horizonColor({ Math::color(246), Math::color(176), Math::color(133) }),
        m_terrainColor0({ Math::color(115), Math::color(69), Math::color(35) }),
        m_terrainColor1({ Math::color(57), Math::color(118), Math::color(40) }),
        m_terrainColor2({ Math::color(45), Math::color(58), Math::color(61) }),
        m_terrainColor3({ Math::color(255), Math::color(255), Math::color(255) })
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

    const glm::vec3& skyColor() const noexcept
    {
        return m_skyColor;
    }

    const glm::vec3& horizonColor() const noexcept
    {
        return m_horizonColor;
    }

    const glm::vec3& terrainColor0() const noexcept
    {
        return m_terrainColor0;
    }

    const glm::vec3& terrainColor1() const noexcept
    {
        return m_terrainColor1;
    }

    const glm::vec3& terrainColor2() const noexcept
    {
        return m_terrainColor2;
    }

    const glm::vec3& terrainColor3() const noexcept
    {
        return m_terrainColor3;
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
    glm::vec3 m_skyColor;
    glm::vec3 m_horizonColor;
    glm::vec3 m_terrainColor0;
    glm::vec3 m_terrainColor1;
    glm::vec3 m_terrainColor2;
    glm::vec3 m_terrainColor3;
};
