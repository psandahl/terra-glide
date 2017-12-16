#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "Program.h"
#include "Viewport.h"
#include "Vertex.h"
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
        m_dummyProgram(),
        m_dummyMesh()
    {}
    TerraGlide(const TerraGlide&) = default;
    ~TerraGlide() = default;

    TerraGlide& operator=(const TerraGlide&) = default;

    TerraGlideStatus setup() noexcept;
    TerraGlideStatus frame(const Viewport& viewport, double duration) noexcept;
    void teardown() noexcept;

private:
    static void initialSettings() noexcept;
    static Camera initialCamera() noexcept
    {
        return { glm::vec3(0, 0, 5), {glm::radians(180.0f), 0.0f},{ glm::radians(180.0f), 0.0f } };
    }
    static glm::mat4 perspectiveViewport(const Viewport& viewport) noexcept
    {
        return glm::perspectiveFov(glm::radians(45.0f), 
            static_cast<float>(std::get<0>(viewport)), 
            static_cast<float>(std::get<1>(viewport)), 
            0.1f, 100.0f);
    }
    static void setViewport(const Viewport& viewport) noexcept
    {
        auto[width, height] = viewport;
        glViewport(0, 0, width, height);
    }

    //Camera m_mainCamera;
    Camera m_camera;
    std::shared_ptr<Program> m_dummyProgram;
    std::shared_ptr<Mesh> m_dummyMesh;
};
