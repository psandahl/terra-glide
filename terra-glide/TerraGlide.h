#pragma once

#include "Mesh.h"
#include "Program.h"
#include "Viewport.h"
#include "Vertex.h"
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
    TerraGlide(const TerraGlide&) = delete;
    TerraGlide(const TerraGlide&&) = delete;
    ~TerraGlide() = default;

    TerraGlide& operator=(const TerraGlide&) = delete;

    TerraGlideStatus setup() noexcept;
    TerraGlideStatus frame(const Viewport& viewport, double duration) noexcept;
    void teardown() noexcept;

private:
    std::shared_ptr<Program> m_dummyProgram;
};
