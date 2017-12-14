#include "Program.h"
#include "TerraGlide.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <iostream>
#include <variant>

TerraGlideStatus TerraGlide::setup() noexcept
{
    auto dummyProgram = makeProgram({ {ShaderType::Vertex, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\dummy-vert.glsl"} });
    if (std::holds_alternative<std::string>(dummyProgram))
    {
        std::cerr << "Error: " << std::get<0>(dummyProgram) << std::endl;
        return TerraGlideStatus::Stop;
    }

    m_dummyProgram = std::get<1>(dummyProgram);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    return TerraGlideStatus::Continue;
}

TerraGlideStatus TerraGlide::frame(const Viewport& viewport, double duration) noexcept
{
    auto[width, height] = viewport;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    return TerraGlideStatus::Continue;
}

void TerraGlide::teardown() noexcept
{
}
