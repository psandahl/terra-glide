#include "Terrain.h"
#include "Tile.h"
#include <glm\vec3.hpp>
#include <iostream>
#include <vector>

void Terrain::prepare(const glm::vec3& position)
{
    std::vector<TileAddress> wantedSet;
    calcWantedSet(position, wantedSet);

    std::vector<TileAddress> purgeSet;
    calcPurgeSet(wantedSet, m_currentTileAddresses, purgeSet);
}

void Terrain::calcWantedSet(const glm::vec3& position,
    std::vector<TileAddress>& wantedSet) const
{
    auto xpos = position.x;
    auto zpos = position.z;
    auto tiles = (TileVista * 2.0f) / static_cast<float>(Tile::TileSquares);
    auto stride = (TileVista * 2.0f) / tiles;
    auto startx = xpos - TileVista;
    auto endx = xpos + TileVista;
    auto startz = zpos - TileVista;
    auto endz = zpos + TileVista;

    for (auto z = startz; z < endz; z += stride)
    {
        for (auto x = startx; x < endx; x += stride)
        {
            wantedSet.push_back(Tile::mkTileAddress(x, z));
        }
    }
}

void Terrain::calcPurgeSet(const std::vector<TileAddress>& wantedSet,
    const std::vector<TileAddress>& currentSet,
    std::vector<TileAddress>& purgeSet) const
{
}