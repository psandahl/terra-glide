#include "Vertex.h"
#include <cstddef>
#include <glad\glad.h>

void VerticesWithPosition::setAttributesInBoundBuffer() noexcept
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(VertexWithPosition), nullptr);
}

void VerticesWithPositionAndNormal::setAttributesInBoundBuffer() noexcept
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(VertexWithPositionAndNormal), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        sizeof(VertexWithPositionAndNormal), 
        reinterpret_cast<const void*>(offsetof(VertexWithPositionAndNormal, normal)));
}