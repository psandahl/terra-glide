#pragma once

#include <glm\common.hpp>
#include <tuple>

using TileAddress = std::tuple<int, int>;

class Tile
{
public:
    static constexpr int TileSquares = 3;
    static constexpr int MaxTiles = 100;
    //static const int TileVertices = TileSquares;

    Tile() = default;
    Tile(const Tile&) = delete;
    ~Tile() = default;

    Tile& operator=(const Tile&) = delete;

    // For a given coordinate x, z give its start tile adress.
    // The coordinate will be clamped within [0, MaxTiles * TileSquares].
    static TileAddress tileAddress(float xpos, float zpos) noexcept
    {
        auto x = glm::clamp(static_cast<int>(xpos), 0, TileSquares * MaxTiles);
        auto z = glm::clamp(static_cast<int>(zpos), 0, TileSquares * MaxTiles);
        return { (x / TileSquares) * TileSquares, 
                 (z / TileSquares) * TileSquares };
    }
};
