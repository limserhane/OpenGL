#include <us/VertexBuffer.hpp>

VertexBuffer::VertexBuffer(unsigned pVertexCount, size_t pVertexSize, void* pVertices):
    vbo(0)
{
	// VBO
	glGenBuffers(1, &vbo);
	bind();
	glBufferData(GL_ARRAY_BUFFER, pVertexCount * pVertexSize, pVertices, GL_STATIC_DRAW);
	unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}