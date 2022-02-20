#include <us/IndexBuffer.hpp>

IndexBuffer::IndexBuffer(unsigned pIndexCount, const unsigned *pIndices):
    ibo(0),
    count(pIndexCount)
{
	glGenBuffers(1, &ibo);
	bind(),
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndexCount * sizeof(unsigned), pIndices, GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ibo);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}