#pragma once

#include "CameraNavigation.h"
#include "Environment.h"
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <glm\trigonometric.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>

// Direction; heading and elevation in radians. Zero heading
// points in positive z direction. Positive elevation points
// above horizon.
struct Direction
{
    float heading;
    float elevation;
};

class Camera
{
public:
    Camera() = delete;

    // Construct a Camera from a position, a direction where to look and a
    // direction where to move.
    Camera(const glm::vec3& position,
        const Direction& viewDirection,
        const Direction& moveDirection) :
        m_position(position),
        m_viewVector(fromEulerAngles(viewDirection.heading, viewDirection.elevation)),
        m_moveVector(fromEulerAngles(moveDirection.heading, moveDirection.elevation)),
        m_viewDirection(viewDirection),
        m_moveDirection(moveDirection)
    {
    }

    Camera(const Camera&) = default;
    ~Camera() = default;

    Camera& operator=(const Camera&) = default;

    // From the Camera, produce a view matrix.
    glm::mat4 matrix() const noexcept
    {
        return glm::lookAt(m_position,
            moveTo(m_position, m_viewVector, Vista),
            glm::vec3(0, 1, 0));
    }

    // Move the Camera position forward according to the move vector and the
    // given distance.
    void moveForward(float distance) noexcept
    {
        m_position = moveTo(m_position, m_moveVector, distance);
    }

    // Move the Camera position backward according to the move vector and
    // the given distance.
    void moveBackward(float distance) noexcept
    {
        m_position = moveTo(m_position, -m_moveVector, distance);
    }

    // Move the camera up the given distance.
    void moveUp(float distance) noexcept
    {
        m_position.y += distance;
    }

    // Move the camera down the given distance.
    void moveDown(float distance) noexcept
    {
        m_position.y -= distance;
    }

    // Turn the move and view directions to the right using the given angle.
    void turnRight(float theta) noexcept
    {
        turn(-theta);
    }

    // Turn the move and view directions to left using the given angle.
    void turnLeft(float theta) noexcept
    {
        turn(theta);
    }

    // Turn the view direction to the right using the given angle.
    void viewRight(float theta) noexcept
    {
        changeViewHeading(-theta);
    }

    // Turn the view direction to the left using the given angle.
    void viewLeft(float theta) noexcept
    {
        changeViewHeading(theta);
    }

    // Turn the view elevation up using the given angle.
    void viewUp(float theta) noexcept
    {
        changeViewElevation(theta);
    }

    // Turn the view elevation down using the given angle.
    void viewDown(float theta) noexcept
    {
        changeViewElevation(-theta);
    }

    // Animate the camera according to the duration.
    void animate(const Environment& environment,
        const CameraNavigation& navigation,
        float duration) noexcept;

private:
    // From heading and elevation angles make a 3D vector representing the
    // direction. Zero heading represents a direction pointing in positive
    // z direction. A positive elevation if pointing above the horizon and a
    // negative elevation is pointing below.
    // Angles are in radians.
    static glm::vec3 fromEulerAngles(float heading, float elevation);

    static float clampElevation(float angle) noexcept
    {
        return glm::clamp(angle, -HalfPi + 0.01f, HalfPi - 0.01f);
    }

    static glm::vec3 moveTo(const glm::vec3& position,
        const glm::vec3& direction,
        float distance)
    {
        return position + (direction * distance);
    }

    void turn(float theta) noexcept
    {
        changeMoveHeading(theta);
        changeViewHeading(theta);
    }

    void changeViewHeading(float theta) noexcept
    {
        m_viewDirection.heading += theta;
        m_viewVector = fromEulerAngles(m_viewDirection.heading, 
            m_viewDirection.elevation);
    }

    void changeViewElevation(float theta) noexcept
    {
        m_viewDirection.elevation = 
            clampElevation(m_viewDirection.elevation + theta);
        m_viewVector = fromEulerAngles(m_viewDirection.heading, 
            m_viewDirection.elevation);
    }

    void changeMoveHeading(float theta) noexcept
    {
        m_moveDirection.heading += theta;
        m_moveVector = fromEulerAngles(m_moveDirection.heading, 
            m_moveDirection.elevation);
    }

    static constexpr float Vista = 10.0f;
    static constexpr float HalfPi = 3.14159265358979f / 2.0f;

    glm::vec3 m_position;
    glm::vec3 m_viewVector;
    glm::vec3 m_moveVector;
    Direction m_viewDirection;
    Direction m_moveDirection;
};
