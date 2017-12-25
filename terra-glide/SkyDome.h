#pragma once

#include "Environment.h"
#include "Mesh.h"
#include "Program.h"
#include <glm\mat4x4.hpp>
#include <memory>
#include <string>
#include <variant>

class SkyDome;

std::variant<std::string, std::shared_ptr<SkyDome>> makeSkyDome();

class SkyDome
{
public:
    SkyDome() = delete;
    SkyDome(std::shared_ptr<Program> program, std::shared_ptr<Mesh> mesh):
        m_program(program),
        m_mesh(mesh)
    {}
    SkyDome(const SkyDome&) = delete;
    ~SkyDome() = default;

    SkyDome& operator=(const SkyDome&) = delete;

    void render(const glm::mat4& perspective, 
        const::glm::mat4& view, 
        const Environment& environment) noexcept;

    void release() noexcept;

private:
    std::shared_ptr<Program> m_program;
    std::shared_ptr<Mesh> m_mesh;
};

