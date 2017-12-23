#include "Mesh.h"
#include "Tile.h"
#include "Vertex.h"
#include <glm\vec3.hpp>
#include <memory>
#include <vector>

std::vector<VertexWithPositionAndNormal> vertices(const TileAddress& address);

std::shared_ptr<Tile> makeTile(const TileAddress& address,
    std::shared_ptr<Program> program,
    std::shared_ptr<std::vector<GLuint>> indices)
{
    MeshRequest request
        { Primitive::Triangles, 
          std::make_shared<VerticesWithPositionAndNormal>(vertices(address)), 
          indices 
        };

    auto mesh = makeMesh(request);

    return std::make_shared<Tile>(address, program, mesh);
}

std::vector<VertexWithPositionAndNormal> vertices(const TileAddress& address)
{
    auto[startx, startz] = address;
    auto numVertices = (Tile::TileSquares + 1) * (Tile::TileSquares + 1);
    std::vector<VertexWithPositionAndNormal> vertices(numVertices);
    vertices.clear();

    for (auto row = 0; row < Tile::TileSquares + 1; ++row)
    {
        for (auto col = 0; col < Tile::TileSquares + 1; ++col)
        {
            auto x = static_cast<float>(startx + col);
            auto z = static_cast<float>(startz + row);

            vertices.push_back({ glm::vec3(x, 0, z), glm::vec3(1) });
        }
    }

    return vertices;
}