#include "Program.h"
#include "TerraGlide.h"
#include "Vertex.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <iostream>
#include <variant>
#include <vector>

std::shared_ptr<Mesh> makeDummyMesh();

TerraGlideStatus TerraGlide::setup() noexcept
{
    auto dummyProgram = makeProgram({ {ShaderType::Vertex, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\dummy.vert"},
                                      { ShaderType::Fragment, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\dummy.frag" }
                                    });
    if (std::holds_alternative<std::string>(dummyProgram))
    {
        std::cerr << "Error: " << std::get<0>(dummyProgram) << std::endl;
        return TerraGlideStatus::Stop;
    }
    m_dummyProgram = std::get<1>(dummyProgram);
    
    m_dummyMesh = makeDummyMesh();

    initialSettings();

    return TerraGlideStatus::Continue;
}

TerraGlideStatus TerraGlide::frame(const Viewport& viewport, double duration) noexcept
{
    m_camera.animate(m_environment, m_cameraNavigation, static_cast<float>(duration));

    setViewport(viewport);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto persp = perspectiveViewport(viewport);
    auto view = m_camera.matrix();
    auto mvp = persp * view;

    m_dummyProgram->enable();
    m_dummyProgram->setUniform("mvp", mvp);
    m_dummyProgram->setUniform("fragColor", glm::vec3(0, 0, 1));
    m_dummyMesh->enable();
    m_dummyMesh->render();
    m_dummyMesh->disable();
    m_dummyProgram->disable();

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
}

void TerraGlide::leftButtonDown(double xpos, double ypos) noexcept
{
}

void TerraGlide::leftButtonUp(double xpos, double ypos) noexcept
{
}

void TerraGlide::cursorPos(double xpos, double ypos) noexcept
{
}

void TerraGlide::teardown() noexcept
{
    if (m_dummyProgram != nullptr)
    {
        m_dummyProgram->release();
    }
    if (m_dummyMesh != nullptr)
    {
        m_dummyMesh->release();
    }
}

void TerraGlide::initialSettings() noexcept
{
    glClearColor(114.0f / 255.0f, 171.0f / 255.0f, 245.0f / 255.0f, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

std::shared_ptr<Mesh> makeDummyMesh()
{
    std::vector<VertexWithPosition> points({ {glm::vec3(0, 1, 0)},
                                             {glm::vec3(-1, -1, 0)},
                                             {glm::vec3(1, -1, 0)}
                                           });
    VerticesWithPosition vertices(points);
    std::vector<GLuint> indices({ 0, 1, 2 });

    MeshRequest request =
    { Primitive::Triangles,
      std::make_shared<VerticesWithPosition>(vertices),
      std::make_shared<std::vector<GLuint>>(indices)
     };
    return makeMesh(request);
}
