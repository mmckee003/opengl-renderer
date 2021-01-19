#include "Buffer.h"

Vertex_Buffer::Vertex_Buffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &renderer_ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vertex_Buffer::~Vertex_Buffer()
{
	glDeleteBuffers(1, &renderer_ID);
}

void Vertex_Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, renderer_ID);
}

void Vertex_Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}