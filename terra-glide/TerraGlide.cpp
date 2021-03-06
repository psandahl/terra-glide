#include "Math.h"
#include "Program.h"
#include "TerraGlide.h"
#include "Terrain.h"
#include "SkyDome.h"
#include "Vertex.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <cstdlib>
#include <iostream>
#include <variant>
#include <vector>

TerraGlideStatus TerraGlide::setup() noexcept
{
    auto terrain = makeTerrain();
    if (std::holds_alternative<std::string>(terrain))
    {
        std::cerr << "Error: " << std::get<0>(terrain) << std::endl;
        return TerraGlideStatus::Stop;
    }
    m_terrain = std::get<1>(terrain);

    auto skyDome = makeSkyDome();
    if (std::holds_alternative<std::string>(skyDome))
    {
        std::cerr << "Error: " << std::get<0>(skyDome) << std::endl;
        return TerraGlideStatus::Stop;
    }
    m_skyDome = std::get<1>(skyDome);

    initialSettings();

    return TerraGlideStatus::Continue;
}

TerraGlideStatus TerraGlide::frame(const Viewport& viewport, float duration) noexcept
{
    m_camera.animate(m_environment, m_cameraNavigation, duration);
    
    m_terrain->prepare(m_camera.position(), m_environment);

    setViewport(viewport);
    glClear(GL_DEPTH_BUFFER_BIT);

    auto perspective = perspectiveViewport(viewport);
    auto view = m_camera.matrix();

    m_skyDome->render(perspective, view, m_environment);
    m_terrain->render(perspective, view, m_environment);

    return TerraGlideStatus::Continue;
}

void TerraGlide::keyDown(int key) noexcept
{
    if (key == GLFW_KEY_UP)
    {
        m_cameraNavigation.setMoveForward(true);
    }
    else if (key == GLFW_KEY_DOWN)
    {
        m_cameraNavigation.setMoveBackward(true);
    }
    else if (key == GLFW_KEY_PAGE_UP)
    {
        m_cameraNavigation.setMoveUp(true);
    }
    else if (key == GLFW_KEY_PAGE_DOWN)
    {
        m_cameraNavigation.setMoveDown(true);
    }
    else if (key == GLFW_KEY_LEFT)
    {
        m_cameraNavigation.setTurnLeft(true);
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        m_cameraNavigation.setTurnRight(true);
    }
}

void TerraGlide::keyUp(int key) noexcept
{
    if (key == GLFW_KEY_UP)
    {
        m_cameraNavigation.setMoveForward(false);
    }
    else if (key == GLFW_KEY_DOWN)
    {
        m_cameraNavigation.setMoveBackward(false);
    }
    else if (key == GLFW_KEY_PAGE_UP)
    {
        m_cameraNavigation.setMoveUp(false);
    }
    else if (key == GLFW_KEY_PAGE_DOWN)
    {
        m_cameraNavigation.setMoveDown(false);
    }
    else if (key == GLFW_KEY_LEFT)
    {
        m_cameraNavigation.setTurnLeft(false);
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        m_cameraNavigation.setTurnRight(false);
    }
}

void TerraGlide::leftButtonDown(const glm::vec2& pos) noexcept
{
    m_cameraNavigation.setCursorPos(pos);
}

void TerraGlide::cursorPos(const glm::vec2& pos) noexcept
{
    const auto& oldPos = m_cameraNavigation.cursorPos();
    if (auto xDelta = pos.x - oldPos.x; xDelta < 0)
    {
        m_camera.viewLeft(glm::radians(std::abs(xDelta)));
    }
    else
    {
        m_camera.viewRight(glm::radians(xDelta));
    }
    if (auto yDelta = pos.y - oldPos.y; yDelta < 0)
    {
        m_camera.viewDown(glm::radians(std::abs(yDelta)));
    }
    else
    {
        m_camera.viewUp(glm::radians(yDelta));
    }

    m_cameraNavigation.setCursorPos(pos);
}

void TerraGlide::teardown() noexcept
{
    m_terrain->release();
    m_skyDome->release();
}

void TerraGlide::initialSettings() noexcept
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
