#pragma once

#include <GL/glew.h>
#include <glimac/common.hpp>

#include <memory>

class IndexBuffer
{
	GLuint ibo;
    unsigned count;

public :
    IndexBuffer(unsigned pIndexCount, const unsigned *pIndices);

    ~IndexBuffer();

    unsigned getCount() const { return count; }

    void bind() const;
    void unbind() const;
};
using IndexBufferPtr = std::shared_ptr<IndexBuffer>;