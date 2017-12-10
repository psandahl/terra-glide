#pragma once

#include "Viewport.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

/// <summary>
/// The bootstrapping function for TerraGlide. The function will run
/// until TerraGlide is terminated.
/// </summary>
int runTerraGlide(Viewport initialViewport);

class Kernel
{
public:
    Kernel(GLFWwindow* window, Viewport& viewport) :
        m_window(window),
        m_viewport(viewport)
    {
    }

    ~Kernel() = default;

    Kernel() = delete;
    Kernel(const Kernel&) = delete;
    Kernel& operator=(const Kernel&) = delete;

    void applyGlobalSettings() const;
    void renderLoop() const;

    void setViewport(int width, int height) noexcept
    {
        m_viewport = std::make_tuple(width, height);
    }

private:
    GLFWwindow* m_window;
    Viewport m_viewport;
};
