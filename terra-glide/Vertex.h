#pragma once

#include "Attributes.h"
#include <glm\vec3.hpp>
#include <vector>

struct VertexWithPosition
{
    glm::vec3 position;
};

class VerticesWithPosition : public Attributes
{
public:
    VerticesWithPosition() = delete;
    VerticesWithPosition(const std::vector<VertexWithPosition>& vertices):
        m_vertices(vertices)
    {}
    ~VerticesWithPosition() = default;

    VerticesWithPosition& operator=(const VerticesWithPosition&) = delete;

    virtual void setAttributesInBoundBuffer() noexcept;
    virtual std::size_t storageSize() const noexcept
    {
        return sizeof(VertexWithPosition) * m_vertices.size();
    }
    virtual const void* raw() const noexcept
    {
        return m_vertices.data();
    }

private:
    std::vector<VertexWithPosition> m_vertices;
};
