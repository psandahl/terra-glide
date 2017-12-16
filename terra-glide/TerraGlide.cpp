#include "Program.h"
#include "TerraGlide.h"
#include "Vertex.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <glm\vec3.hpp>
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


    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    return TerraGlideStatus::Continue;
}

TerraGlideStatus TerraGlide::frame(const Viewport& viewport, double duration) noexcept
{
    auto[width, height] = viewport;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    m_dummyProgram->enable();
    m_dummyProgram->setUniform("fragColor", glm::vec3(0, 0, 1));
    m_dummyMesh->enable();
    m_dummyMesh->render();
    m_dummyMesh->disable();
    m_dummyProgram->disable();

    return TerraGlideStatus::Continue;
}

void TerraGlide::teardown() noexcept
{
}

std::shared_ptr<Mesh> makeDummyMesh()
{
    std::vector<VertexWithPosition> points({ {glm::vec3(0, 1, 0)},
                                             {glm::vec3(-1, -1, 1)},
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
