#include <glad\glad.h>
#include "Vertex.h"

void VerticesWithPosition::setAttributesInBoundBuffer() noexcept
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(VertexWithPosition), nullptr);
}