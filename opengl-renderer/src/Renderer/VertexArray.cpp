#include "VertexArray.h"

Vertex_Array::Vertex_Array()
{
	glGenVertexArrays(1, &renderer_ID);
}

Vertex_Array::~Vertex_Array()
{
	glDeleteVertexArrays(1, &renderer_ID);
}

void Vertex_Array::bind() const
{
	glBindVertexArray(renderer_ID);
}

void Vertex_Array::unbind() const
{
	glBindVertexArray(0);
}

void Vertex_Array::set_vertex_buffer(Vertex_Buffer* _vertex_buffer)
{
	bind();
	_vertex_buffer->bind();
	vertex_buffer = _vertex_buffer;

	// TODO: glEnableVertexAttribArray(...)
	// We need to do this to bind this vbo to the vao's state
	// hard coding this now but probably should change down the line
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Vertex_Array::set_index_buffer(Index_Buffer* _index_buffer)
{
	bind();
	_index_buffer->bind();
	index_buffer = _index_buffer;
}
