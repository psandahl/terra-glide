#include "Tile.h"
#include "Vertex.h"
#include <vector>

std::shared_ptr<Tile> makeTile(const TileAddress& address,
    std::shared_ptr<Program> program,
    std::shared_ptr<std::vector<GLuint>> indices)
{
    auto[startx, startz] = address;
    auto numVertices = (Tile::TileSquares + 1) * (Tile::TileSquares + 1);
    std::vector<VertexWithPosition> vertices(numVertices);
    vertices.clear();

    return nullptr;
}