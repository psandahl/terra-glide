#pragma once

class Environment
{
public:
    Environment():
        m_horizontalSpeed(2),
        m_verticalSpeed(2)
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

private:
    float m_horizontalSpeed;
    float m_verticalSpeed;
};
