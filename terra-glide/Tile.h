#pragma once

#include "Mesh.h"
#include "Program.h"
#include "Vertex.h"
#include <glad\glad.h>
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <memory>
#include <tuple>
#include <vector>

using TileAddress = std::tuple<int, int>;

class Tile;

std::shared_ptr<Tile> makeTile(const TileAddress& address, 
    std::shared_ptr<Program> program, 
    std::shared_ptr<std::vector<GLuint>> indices);

class Tile
{
public:
    static constexpr int TileSquares = 3;
    static constexpr int MaxTiles = 1000000;

    Tile(const TileAddress& address,
        std::shared_ptr<Program> program,
        std::shared_ptr<Mesh> mesh) :
        m_address(address),
        m_program(program),
        m_mesh(mesh)
    {}
    Tile() = delete;
    Tile(const Tile&) = delete;
    ~Tile() = default;

    Tile& operator=(const Tile&) = delete;

    const TileAddress& tileAddress() const noexcept
    {
        return m_address;
    }

    // For a given coordinate x, z give its start tile address.
    // The coordinate will be clamped within [0, MaxTiles * TileSquares].
    static TileAddress mkTileAddress(float xpos, float zpos) noexcept
    {
        auto x = glm::clamp(static_cast<int>(xpos), 0, TileSquares * MaxTiles);
        auto z = glm::clamp(static_cast<int>(zpos), 0, TileSquares * MaxTiles);
        return { (x / TileSquares) * TileSquares, 
                 (z / TileSquares) * TileSquares };
    }

    // Make indices for the tiles.
    static std::shared_ptr<std::vector<GLuint>> mkIndices()
    {
        auto indices = std::make_shared<std::vector<GLuint>>(TileSquares * TileSquares * 6);
        indices->clear();
        for (auto square = 0; square < TileSquares * TileSquares; ++square)
        {
            auto startVert = (square / TileSquares) * (TileSquares + 1) + (square % TileSquares);
            indices->push_back(startVert + 1);
            indices->push_back(startVert);
            indices->push_back(startVert + TileSquares + 1);
            indices->push_back(startVert + 1);
            indices->push_back(startVert + TileSquares + 1);
            indices->push_back(startVert + TileSquares + 2);
        }

        return indices;
    }

    void render(const glm::mat4& vp) noexcept
    {
        // Program is already activated. Mesh is already
        // in world space.
        m_program->setUniform("mvp", vp);
        m_mesh->enable();
        m_mesh->render();
        m_mesh->disable();
    }

private:
    TileAddress m_address;
    std::shared_ptr<Program> m_program;
    std::shared_ptr<Mesh> m_mesh;
};
