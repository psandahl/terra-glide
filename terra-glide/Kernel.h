#pragma once

#include "TerraGlide.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <memory>

/// <summary>
/// The bootstrapping function for TerraGlide. The function will run
/// until TerraGlide is terminated.
/// </summary>
int runTerraGlide(Viewport initialViewport);

class Kernel
{
public:
    Kernel(GLFWwindow* window, 
           Viewport& viewport, 
           std::shared_ptr<TerraGlide> terraGlide,
           double now) :
        m_window(window),
        m_viewport(viewport),
        m_lastTimestamp(now)
    {
    }

    ~Kernel() = default;

    Kernel() = delete;
    Kernel(const Kernel&) = delete;
    Kernel& operator=(const Kernel&) = delete;

    void renderLoop() noexcept;

    void setViewport(int width, int height) noexcept
    {
        m_viewport = std::make_tuple(width, height);
    }

private:
    GLFWwindow* m_window; // Plain old pointer.
    Viewport m_viewport;
    std::shared_ptr<TerraGlide> m_terraGlide;
    double m_lastTimestamp;

};
