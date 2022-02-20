#pragma once

#include <GL/glew.h>
#include <glimac/common.hpp>
#include <memory>

class VertexBuffer
{
private:
	GLuint vbo;

public:
    VertexBuffer(unsigned pVertexCount, size_t pVertexSize, void* pVertices);

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
using VertexBufferPtr = std::shared_ptr<VertexBuffer>;