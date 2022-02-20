#pragma once

#include <GL/glew.h>
#include <glimac/common.hpp>
#include <us/VertexBuffer.hpp>
#include <us/IndexBuffer.hpp>
#include <memory>

class VertexArray
{
private:
	GLuint vao;
    IndexBufferPtr indices;

public:
    VertexArray(VertexBufferPtr vertices, IndexBufferPtr indices);

    ~VertexArray();

    void bind() const;
    void unbind() const;

    void draw() const;
};
using VertexArrayPtr = std::shared_ptr<VertexArray>;