#pragma once

#include "Program.h"
#include "Tile.h"
#include <glm\vec3.hpp>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class Terrain;

std::variant<std::string, std::shared_ptr<Terrain>> makeTerrain();

class Terrain
{
public:
    Terrain() = delete;
    Terrain(std::shared_ptr<Program> program):
        m_program(program)
    {}
    Terrain(const Terrain&) = delete;
    ~Terrain() = default;

    Terrain& operator=(const Terrain&) = delete;

    // Prepare the terrain (i.e. manage tiles) for this position.
    void prepare(const glm::vec3& position);

private:

    void calcWantedSet(const glm::vec3& position, 
        std::vector<TileAddress>& wantedSet) const;

    void calcPurgeSet(const std::vector<TileAddress>& wantedSet, 
        const std::vector<TileAddress>& currentSet, 
        std::vector<TileAddress>& purgeSet) const;

    void calcAddSet(const std::vector<TileAddress>& wantedSet,
        const std::vector<TileAddress>& currentSet,
        std::vector<TileAddress>& purgeSet) const;

    void purgeStuff(const std::vector<TileAddress>& purgeSet);

    void addStuff(const std::vector<TileAddress>& addSet);

    // How far - N, W, S, E - can the camera see from its
    // current position with regards to how many tiles must
    // be loaded. Not same as far plane.
    static constexpr float TileVista = 5.0f;

    std::shared_ptr<Program> m_program;
    std::vector<std::shared_ptr<Tile>> m_tiles;
    std::vector<TileAddress> m_currentTileAddresses;
};
