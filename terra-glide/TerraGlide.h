#pragma once

#include "Camera.h"
#include "CameraNavigation.h"
#include "Environment.h"
#include "Terrain.h"
#include "Viewport.h"
#include "Vertex.h"
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <memory>

enum class TerraGlideStatus
{
    Continue,
    Stop
};

class TerraGlide
{
public:
    TerraGlide():
        m_camera(initialCamera()),
        m_cameraNavigation(),
        m_environment(),
        m_terrain()
    {}
    TerraGlide(const TerraGlide&) = default;
    ~TerraGlide() = default;

    TerraGlide& operator=(const TerraGlide&) = default;

    TerraGlideStatus setup() noexcept;
    TerraGlideStatus frame(const Viewport& viewport, float duration) noexcept;
    void keyDown(int key) noexcept;
    void keyUp(int key) noexcept;
    void leftButtonDown(const glm::vec2& pos) noexcept;
    void cursorPos(const glm::vec2& pos) noexcept;
    void teardown() noexcept;

private:
    static void initialSettings() noexcept;
    static Camera initialCamera() noexcept
    {
        return { glm::vec3(1000, 3, 1000), {glm::radians(180.0f), 0.0f}, { glm::radians(180.0f), 0.0f } };
    }
    static glm::mat4 perspectiveViewport(const Viewport& viewport) noexcept
    {
        return glm::perspectiveFov(glm::radians(45.0f), 
            static_cast<float>(std::get<0>(viewport)), 
            static_cast<float>(std::get<1>(viewport)), 
            0.1f, 500.0f);
    }
    static void setViewport(const Viewport& viewport) noexcept
    {
        auto[width, height] = viewport;
        glViewport(0, 0, width, height);
    }

    Camera m_camera;
    CameraNavigation m_cameraNavigation;
    Environment m_environment;
    std::shared_ptr<Terrain> m_terrain;
};
