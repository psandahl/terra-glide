#include "Camera.h"
#include "CameraNavigation.h"
#include "Environment.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Camera::animate(const Environment& environment,
    const CameraNavigation& navigation,
    float duration) noexcept
{
    auto distance = duration * environment.moveSpeed();

    if (navigation.moveForward())
    {
        moveForward(distance);
    }

    if (navigation.moveBackward())
    {
        moveBackward(distance);
    }
}

glm::vec3 Camera::fromEulerAngles(float heading, float elevation)
{
    auto pitch = glm::rotate(glm::mat4(1), -elevation, glm::vec3(1, 0, 0));
    auto yaw = glm::rotate(glm::mat4(1), heading, glm::vec3(0, 1, 0));
    auto rotation = yaw * pitch;
    auto direction = rotation * glm::vec4(0, 0, 1, 0);

    return glm::vec3(direction.x, direction.y, direction.z);
}