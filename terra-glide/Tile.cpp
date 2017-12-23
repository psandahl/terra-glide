#include "Mesh.h"
#include "Tile.h"
#include "Vertex.h"
#include <glm\vec3.hpp>
#include <glm\gtc\noise.hpp>
#include <memory>
#include <vector>

std::vector<VertexWithPositionAndNormal> vertices(const TileAddress& address, std::shared_ptr<std::vector<GLuint>> indices);
void genSmoothNormals(std::vector<VertexWithPositionAndNormal>& vertices, std::shared_ptr<std::vector<GLuint>> indices);
glm::vec3 surfaceNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
float terrainHeight(float x, float z);

std::shared_ptr<Tile> makeTile(const TileAddress& address,
    std::shared_ptr<Program> program,
    std::shared_ptr<std::vector<GLuint>> indices)
{
    MeshRequest request
        { Primitive::Triangles, 
          std::make_shared<VerticesWithPositionAndNormal>(vertices(address, indices)), 
          indices 
        };

    auto mesh = makeMesh(request);

    return std::make_shared<Tile>(address, program, mesh);
}

std::vector<VertexWithPositionAndNormal> vertices(const TileAddress& address, std::shared_ptr<std::vector<GLuint>> indices)
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

            vertices.push_back({ glm::vec3(x, terrainHeight(x, z), z), glm::vec3(0) });
        }
    }

    genSmoothNormals(vertices, indices);

    return vertices;
}

void genSmoothNormals(std::vector<VertexWithPositionAndNormal>& vertices, std::shared_ptr<std::vector<GLuint>> indices)
{
    std::size_t index = 0;
    while ((index + 3) < indices->size())
    {
        auto v1 = indices->at(index);
        auto v2 = indices->at(index + 1);
        auto v3 = indices->at(index + 2);

        auto normal = surfaceNormal(
            vertices[v1].position, 
            vertices[v2].position, 
            vertices[v3].position);

        vertices[v1].normal += normal;
        vertices[v2].normal += normal;
        vertices[v3].normal += normal;

        index += 3;
    }

    for (auto vertex : vertices)
    {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

glm::vec3 surfaceNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
{
    auto vec1 = v2 - v1;
    auto vec2 = v3 - v1;

    return glm::normalize(glm::cross(vec1, vec2));
}

float terrainHeight(float x, float z)
{
    glm::vec3 v(x, 0, z);
    return glm::simplex(v);
}