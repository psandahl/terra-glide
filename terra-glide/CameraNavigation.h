#pragma once

class CameraNavigation
{
public:
    CameraNavigation():
        m_moveForward(false),
        m_moveBackward(false)
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

private:
    bool m_moveForward;
    bool m_moveBackward;
};
