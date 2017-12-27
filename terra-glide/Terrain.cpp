#include "Math.h"
#include "Program.h"
#include "Terrain.h"
#include "Tile.h"
#include <algorithm>
#include <glm\vec3.hpp>
//#include <iostream>
#include <iterator>
#include <variant>
#include <vector>

std::variant<std::string, std::shared_ptr<Terrain>> makeTerrain()
{
    auto program = 
        makeProgram(
        { 
            { ShaderType::Vertex, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\terrain-tile.vert" },
            { ShaderType::Fragment, "\\Users\\patri\\source\\repos\\terra-glide\\resources\\shaders\\terrain-tile.frag" }
        });

    if (std::holds_alternative<std::string>(program))
    {
        return { std::get<0>(program) };
    }
 
    return { std::make_shared<Terrain>(std::get<1>(program)) };
}

/*void printSet(const std::vector<TileAddress>& addresses)
{
    for (auto[x, z] : addresses)
    {
        std::cout << "address x=" << x << ", z=" << z << std::endl;
    }
}*/

void Terrain::prepare(const glm::vec3& position, const Environment& environment)
{
    updateTileVista();

    //std::cout << "-----------\n";
    //std::cout << "Prepare for position x=" << position.x << ", z=" << position.z << std::endl;

    std::vector<TileAddress> wantedSet;
    calcWantedSet(position, wantedSet);
    std::sort(wantedSet.begin(), wantedSet.end()); // Temporary hack

    //std::cout << "Wanted set\n\n";
    //printSet(wantedSet);

    std::vector<TileAddress> purgeSet;
    calcPurgeSet(wantedSet, m_currentTileAddresses, purgeSet);
    //std::sort(purgeSet.begin(), purgeSet.end()); // Temporary hack
    //std::cout << "\nPurge set\n\n";
    //printSet(purgeSet);

    purgeStuff(purgeSet);
    //std::cout << "\nPurged current set\n\n";
    //printSet(m_currentTileAddresses);

    std::vector<TileAddress> addSet;
    calcAddSet(wantedSet, m_currentTileAddresses, addSet);
    //std::sort(addSet.begin(), addSet.end());
    //std::cout << "\nAdd set\n\n";
    //printSet(addSet);

    addStuff(addSet, environment);
    //std::cout << "\nAdded current set\n\n";
    //printSet(m_currentTileAddresses);
}

void Terrain::render(const glm::mat4& perspective,
    const glm::mat4& view,
    const Environment& environment) noexcept
{
    //GLint polygonMode[2];
    //glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Tiles are already in world space.
    auto vpMatrix = perspective * view;

    m_program->enable();
    m_program->setUniform("mvpMatrix", vpMatrix);
    m_program->setUniform("viewMatrix", view);
    m_program->setUniform("normalMatrix", Math::normalMatrix(view));
    m_program->setUniform("terrainHeight", environment.terrainHeight());
    m_program->setUniform("terrainColor0", environment.terrainColor0());
    m_program->setUniform("terrainColor1", environment.terrainColor1());
    m_program->setUniform("terrainColor2", environment.terrainColor2());
    m_program->setUniform("terrainColor3", environment.terrainColor3());
    m_program->setUniform("ambientColor", environment.ambientColor());
    m_program->setUniform("ambientStrength", environment.ambientStrength());
    m_program->setUniform("sunDirection", 
        transformSunDirection(view, environment.sunDirection()));
    m_program->setUniform("sunColor", environment.sunColor());
    m_program->setUniform("fogColor", environment.fogColor());
    m_program->setUniform("fogIntensity", environment.fogIntensity());

    for (auto tile : m_tiles)
    {
        tile->render();
    }
    m_program->disable();

    //glPolygonMode(polygonMode[0], polygonMode[1]);
}

void Terrain::release() noexcept
{
    for (auto tile : m_tiles)
    {
        tile->release();
    }
    m_program->release();
}

void Terrain::calcWantedSet(const glm::vec3& position,
    std::vector<TileAddress>& wantedSet) const
{
    auto xpos = position.x;
    auto zpos = position.z;
    auto tiles = (m_tileVista * 2.0f) / static_cast<float>(Tile::TileSquares);
    auto stride = (m_tileVista * 2.0f) / tiles;
    auto startx = xpos - m_tileVista;
    auto endx = xpos + m_tileVista;
    auto startz = zpos - m_tileVista;
    auto endz = zpos + m_tileVista;

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
    std::set_difference(currentSet.begin(), currentSet.end(),
        wantedSet.begin(), wantedSet.end(),
        std::inserter(purgeSet, purgeSet.begin()));
}

void Terrain::calcAddSet(const std::vector<TileAddress>& wantedSet,
    const std::vector<TileAddress>& currentSet,
    std::vector<TileAddress>& addSet) const
{
    std::set_difference(wantedSet.begin(), wantedSet.end(),
        currentSet.begin(), currentSet.end(),
        std::back_inserter(addSet));
}

void Terrain::purgeStuff(const std::vector<TileAddress>& purgeSet)
{
    for (auto it = m_tiles.begin(); it != m_tiles.end();)
    {
        if (std::find(purgeSet.begin(), purgeSet.end(), (*it)->tileAddress()) != purgeSet.end())
        {
            (*it)->release();
            it = m_tiles.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = m_currentTileAddresses.begin(); it != m_currentTileAddresses.end();)
    {
        if (std::find(purgeSet.begin(), purgeSet.end(), *it) != purgeSet.end())
        {
            it = m_currentTileAddresses.erase(it);
        }
        else
        {
            ++it;
        }
    }

    std::sort(m_currentTileAddresses.begin(), m_currentTileAddresses.end());
}

void Terrain::addStuff(const std::vector<TileAddress>& addSet, 
    const Environment& environment)
{
    // Make new Tiles.
    for (auto address : addSet)
    {
        auto tile = makeTile(address, m_program, m_indices, environment);
        m_tiles.push_back(tile);
    }

    // Update the address set.
    std::copy(addSet.begin(), addSet.end(), std::back_inserter(m_currentTileAddresses));
    std::sort(m_currentTileAddresses.begin(), m_currentTileAddresses.end());
}