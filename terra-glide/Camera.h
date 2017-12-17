#pragma once

#include "CameraNavigation.h"
#include "Environment.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    static glm::vec3 moveTo(const glm::vec3& position,
        const glm::vec3& direction,
        float distance)
    {
        return position + (direction * distance);
    }

    static constexpr float Vista = 10.0f;

    glm::vec3 m_position;
    glm::vec3 m_viewVector;
    glm::vec3 m_moveVector;
    Direction m_viewDirection;
    Direction m_moveDirection;
};
