//#include "Kernel.h"
//#include "Viewport.h"
#include "Terrain.h"
#include "Tile.h"
#include <glm\vec3.hpp>
#include <iostream>

int main()
{
    //return runTerraGlide(std::make_tuple(1024, 768));
    //auto[x, z] = Tile::tileAddress(4, 4);

    //std::cout << x << ", " << z << std::endl;
    Terrain t;

    t.prepare(glm::vec3(20.0f));

    return 0;
}