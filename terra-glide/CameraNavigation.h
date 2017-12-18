#pragma once

class CameraNavigation
{
public:
    CameraNavigation():
        m_moveForward(false),
        m_moveBackward(false),
        m_moveUp(false),
        m_moveDown(false)
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

private:
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveUp;
    bool m_moveDown;
};
