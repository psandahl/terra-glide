#include "Terrain.h"
#include "Tile.h"
#include <glm\vec3.hpp>
#include <iostream>

void Terrain::prepare(const glm::vec3& position) noexcept
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
            auto[tilex, tilez] = Tile::tileAddress(x, z);
            //std::cout << "Raw coords x: " << x << ", z: " << z << std::endl;
            std::cout << "Tile with start x: " << tilex << ", z: " << tilez << std::endl;
        }
    }

    //std::cout << "stride: " << stride << std::endl;
    //std::cout << "tiles: " << tiles << std::endl;
}