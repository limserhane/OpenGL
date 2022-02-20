#include <us/VertexArray.hpp>

VertexArray::VertexArray(VertexBufferPtr pVertices, IndexBufferPtr pIndices):
    vao(0),
    indices(pIndices)
{
	// VAO
	glGenVertexArrays(1, &vao);
	bind();
	pIndices->bind(); //!!!!!! BUG SI PAS AUCUNE REF VERS vertices / indices N EST GARDEE

	// VAO - Position
	const GLuint VERTEX_ATTRIBUTE_POSITION = 0;
	glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
	pVertices->bind();
	glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(glimac::ShapeVertex, position)));
	pVertices->unbind();

	// VAO - Normal
	const GLuint VERTEX_ATTRIBUTE_NORMAL = 1;
	glEnableVertexAttribArray(VERTEX_ATTRIBUTE_NORMAL);
	pVertices->bind();
	glVertexAttribPointer(VERTEX_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(glimac::ShapeVertex, normal)));
	pVertices->unbind();

	// VAO - TexCoords
	const GLuint VERTEX_ATTRIBUTE_TEXCOORDS = 2;
	glEnableVertexAttribArray(VERTEX_ATTRIBUTE_TEXCOORDS);
	pVertices->bind();
	glVertexAttribPointer(VERTEX_ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(glimac::ShapeVertex, texCoords)));
	pVertices->unbind();

	// VAO
	unbind();
    pIndices->unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind() const
{
	glBindVertexArray(vao);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::draw() const
{
	bind();
	glDrawElements(GL_TRIANGLES, indices->getCount(), GL_UNSIGNED_INT, 0);
}
