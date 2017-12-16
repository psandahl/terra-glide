#pragma once

#include "Attributes.h"
#include <glad\glad.h>
#include <memory>
#include <vector>

enum class Primitive
{
    Triangles
};

struct MeshRequest
{
    Primitive primitive;
    std::shared_ptr<Attributes> vertices;
    std::shared_ptr<std::vector<GLuint>> indices;
};

class Mesh;

std::shared_ptr<Mesh> makeMesh(const MeshRequest& request);

class Mesh
{
public:
    Mesh() = delete;
    Mesh(GLuint vao, Primitive primitive, std::shared_ptr<std::vector<GLuint>> indices):
        m_vao(vao),
        m_primitive(primitive),
        m_indices(indices)
    {}
    Mesh(const Mesh&) = default;
    ~Mesh() = default;

    Mesh& operator=(const Mesh&) = default;

    void enable() const noexcept
    {
        glBindVertexArray(m_vao);
    }

    void disable() const noexcept
    {
        glBindVertexArray(0);
    }

    void release() noexcept
    {
        if (m_vao != 0)
        {
            GLuint vaos[1] = { m_vao };
            glDeleteVertexArrays(1, vaos);
            m_vao = 0;
        }
    }

    void render() const noexcept
    {
        glDrawElements(fromPrimitive(m_primitive), m_indices->size(), 
                       GL_UNSIGNED_INT, m_indices->data());
    }

private:
    GLenum fromPrimitive(Primitive primitive) const noexcept
    {
        switch (primitive)
        {
        case Primitive::Triangles:
            return GL_TRIANGLES;

        default:
            return 0;
        }
    }

    GLuint m_vao;
    Primitive m_primitive;
    std::shared_ptr<std::vector<GLuint>> m_indices;
};