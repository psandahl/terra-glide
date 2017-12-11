#pragma once

#include "Event.h"
#include "Link.h"
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
    Kernel(GLFWwindow* window, std::shared_ptr<Link<Event>> events,  
           Viewport& viewport, double now) :
        m_window(window),
        m_events(events),
        m_viewport(viewport),
        m_lastTimestamp(now)
    {
    }

    ~Kernel() = default;

    Kernel() = delete;
    Kernel(const Kernel&) = delete;
    Kernel& operator=(const Kernel&) = delete;

    void applyGlobalSettings() const noexcept;
    void renderLoop() noexcept;
    void scanRequests() noexcept;

    void setViewport(int width, int height) noexcept
    {
        m_viewport = std::make_tuple(width, height);
    }

private:
    GLFWwindow* m_window; // Plain old pointer.
    std::shared_ptr<Link<Event>> m_events;
    Viewport m_viewport;
    double m_lastTimestamp;
};
