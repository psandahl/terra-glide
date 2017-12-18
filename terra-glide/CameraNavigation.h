#pragma once

#include <glm\vec2.hpp>

class CameraNavigation
{
public:
    CameraNavigation():
        m_moveForward(false),
        m_moveBackward(false),
        m_moveUp(false),
        m_moveDown(false),
        m_turnLeft(false),
        m_turnRight(false),
        m_cursorPos(0)
    {}

    CameraNavigation(const CameraNavigation&) = default;
    ~CameraNavigation() = default;

    CameraNavigation& operator=(const CameraNavigation&) = default;

    bool moveForward() const noexcept
    {
        return m_moveForward;
    }
    void setMoveForward(bool value) noexcept
    {
        m_moveForward = value;
    }

    bool moveBackward() const noexcept
    {
        return m_moveBackward;
    }
    void setMoveBackward(bool value) noexcept
    {
        m_moveBackward = value;
    }

    bool moveUp() const noexcept
    {
        return m_moveUp;
    }
    void setMoveUp(bool value) noexcept
    {
        m_moveUp = value;
    }

    bool moveDown() const noexcept
    {
        return m_moveDown;
    }
    void setMoveDown(bool value) noexcept
    {
        m_moveDown = value;
    }

    bool turnLeft() const noexcept
    {
        return m_turnLeft;
    }
    void setTurnLeft(bool value) noexcept
    {
        m_turnLeft = value;
    }

    bool turnRight() const noexcept
    {
        return m_turnRight;
    }
    void setTurnRight(bool value) noexcept
    {
        m_turnRight = value;
    }

    const glm::vec2& cursorPos() const noexcept
    {
        return m_cursorPos;
    }
    void setCursorPos(const glm::vec2& value) noexcept
    {
        m_cursorPos = value;
    }

private:
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveUp;
    bool m_moveDown;
    bool m_turnLeft;
    bool m_turnRight;
    glm::vec2 m_cursorPos;
};
