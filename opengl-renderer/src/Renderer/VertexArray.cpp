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

void Vertex_Array::add_vertex_buffer(const Vertex_Buffer* vertex_buffer)
{

}

void Vertex_Array::set_index_buffer(const Index_Buffer* index_buffer)
{
}
