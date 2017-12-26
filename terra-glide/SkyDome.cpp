#include "Mesh.h"
#include "SkyDome.h"
#include "Vertex.h"
#include <glad\glad.h>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_access.hpp>
#include <vector>

std::vector<VertexWithPosition> vertices();
std::vector<GLuint> indices();

std::variant<std::string, std::shared_ptr<SkyDome>> makeSkyDome()
{
    auto program =
        makeProgram(
            {
                { ShaderType::Vertex, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\sky-dome.vert" },
                { ShaderType::Fragment, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\sky-dome.frag" }
            });

    if (std::holds_alternative<std::string>(program))
    {
        return { std::get<0>(program) };
    }

    MeshRequest request =
    {
        Primitive::Triangles,
        std::make_shared<VerticesWithPosition>(vertices()),
        std::make_shared<std::vector<GLuint>>(indices())
    };

    auto mesh = makeMesh(request);

    return { std::make_shared<SkyDome>(std::get<1>(program), mesh) };
}

void SkyDome::render(const glm::mat4& perspective,
    const::glm::mat4& view,
    const Environment& environment) noexcept
{
    GLint cullMode[1];
    glGetIntegerv(GL_CULL_FACE_MODE, cullMode);
    glCullFace(GL_FRONT);

    GLboolean depthMask[1];
    glGetBooleanv(GL_DEPTH_WRITEMASK, depthMask);
    glDepthMask(GL_FALSE);

    m_program->enable();
    m_mesh->enable();

    // Make the sky dome snap to the camera.
    auto snapToCamera = glm::column(view, 3, { 0.0f, 0.0f, 0.0f, 1.0f });

    auto mvpMatrix = perspective * snapToCamera;
    m_program->setUniform("mvpMatrix", mvpMatrix);
    m_program->setUniform("skyColor", environment.skyColor());
    m_program->setUniform("horizonColor", environment.horizonColor());
    m_program->setUniform("fogColor", environment.fogColor());
    m_mesh->render();

    m_mesh->disable();
    m_program->disable();

    glCullFace(cullMode[0]);
    glDepthMask(depthMask[0]);
}

void SkyDome::release() noexcept
{
    m_program->release();
    m_mesh->release();
}

std::vector<VertexWithPosition> vertices()
{
    return 
    {  
        { {0.0f, 1.0f, 0.0f} },
        { {0.894f, 0.447f, 0.0f} },
        { {0.276f, 0.447f, 0.851f} },
        { {-0.724f, 0.447f, 0.526f} },
        { {-0.724f, 0.447f, -0.526f} },
        { {0.276f, 0.447f, -0.851f} },
        { {0.724f, -0.447f, 0.526f} },
        { {-0.276f, -0.447f, 0.851f} },
        { {-0.894f, -0.447f, 0.0f} },
        { {-0.276f, -0.447f, -0.851f} },
        { {0.724f, -0.447f, -0.526f} },
        { {0.0f, -1.0f, 0.0f} }
    };
}

std::vector<GLuint> indices()
{
    return
    {
        0, 2, 1,
        0, 3, 2,
        0, 4, 3,
        0, 5, 4,
        0, 1, 5,
        11, 6, 7,
        11, 7, 8,
        11, 8, 9,
        11, 9, 10,
        11, 10, 6,
        1, 2, 6,
        2, 3, 7,
        3, 4, 8,
        4, 5, 9,
        5, 1, 10,
        6, 2, 7,
        7, 3, 8,
        8, 4, 9,
        9, 5, 10,
        10, 1, 6
    };
}