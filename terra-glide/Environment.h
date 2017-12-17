#pragma once

class Environment
{
public:
    Environment():
        m_moveSpeed(1)
    {}

    Environment(const Environment&) = default;
    ~Environment() = default;

    Environment& operator=(const Environment&) = default;

    float moveSpeed() const noexcept
    {
        return m_moveSpeed;
    }

private:
    float m_moveSpeed;
};
