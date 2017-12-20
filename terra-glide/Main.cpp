//#include "Kernel.h"
//#include "Viewport.h"
#include "Terrain.h"
#include "Tile.h"
#include <glm\vec3.hpp>
#include <iostream>
#include <vector>

int main()
{
    //return runTerraGlide(std::make_tuple(1024, 768));
    //auto[x, z] = Tile::tileAddress(4, 4);

    //std::cout << x << ", " << z << std::endl;
    Terrain t;

    t.prepare(glm::vec3(20.0f, 0.0f, 20.0f));
    t.prepare(glm::vec3(20.0f, 0.0f, 19.0f));
    t.prepare(glm::vec3(20.0f, 0.0f, 18.0f));

    auto indices(Tile::mkIndices());

    std::cout << indices->size() << std::endl;
    /*for (auto index : indices)
    {
        std::cout << index << std::endl;
    }*/

    return 0;
}