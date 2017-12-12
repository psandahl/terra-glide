#include "TerraGlide.h"
#include "Viewport.h"
#include <glad\glad.h>
#include <iostream>

TerraGlideStatus TerraGlide::setup() noexcept
{
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
