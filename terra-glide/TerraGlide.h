#pragma once

#include "Mesh.h"
#include "Program.h"
#include "Viewport.h"
#include "Vertex.h"
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
    TerraGlide() = default;
    TerraGlide(const TerraGlide&) = default;
    ~TerraGlide() = default;

    TerraGlide& operator=(const TerraGlide&) = default;

    TerraGlideStatus setup() noexcept;
    TerraGlideStatus frame(const Viewport& viewport, double duration) noexcept;
    void teardown() noexcept;

private:
    static void initialSettings() noexcept;
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

    std::shared_ptr<Program> m_dummyProgram;
    std::shared_ptr<Mesh> m_dummyMesh;
};
