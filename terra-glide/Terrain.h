#pragma once

#include <glm\vec3.hpp>

class Terrain
{
public:
    Terrain() = default;
    Terrain(const Terrain&) = delete;
    ~Terrain() = default;

    Terrain& operator=(const Terrain&) = delete;

    // Prepare the terrain (i.e. manage tiles) for this position.
    void prepare(const glm::vec3& position) noexcept;

private:

    // How far - N, W, S, E - can the camera see from its
    // current position.
    static constexpr float TileVista = 10.f;
};
