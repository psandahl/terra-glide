#include "Attributes.h"
#include "Mesh.h"
#include <glad\glad.h>
#include <memory>

GLuint allocBoundBuffers();
void fillVbo(std::shared_ptr<Attributes> vertices);

std::shared_ptr<Mesh> makeMesh(const MeshRequest& request)
{
    auto vao = allocBoundBuffers();
    fillVbo(request.vertices);
    request.vertices->setAttributesInBoundBuffer();
    glBindVertexArray(0);

    return std::make_shared<Mesh>(vao, request.primitive, request.indices);
}

GLuint allocBoundBuffers()
{
    GLuint vaos[1];
    glGenVertexArrays(1, vaos);
    auto[vao] = vaos;
    glBindVertexArray(vao);

    GLuint vbos[1];
    glGenBuffers(1, vbos);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);

    return vao;
}

void fillVbo(std::shared_ptr<Attributes> vertices)
{
    glBufferData(GL_ARRAY_BUFFER, vertices->storageSize(), 
                 vertices->raw(), GL_STATIC_DRAW);
}