#pragma once

#include "Tile.h"
#include <glm\vec3.hpp>
#include <memory>
#include <vector>

class Terrain
{
public:
    Terrain() = default;
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

    // How far - N, W, S, E - can the camera see from its
    // current position.
    static constexpr float TileVista = 10.f;

    //std::vector<std::shared_ptr<Tile>> m_tiles;
    std::vector<TileAddress> m_currentTileAddresses;
};
