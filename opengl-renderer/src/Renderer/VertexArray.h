#pragma once

#include "Buffer.h"

#include <vector>

struct Vertex_Array
{
	unsigned int renderer_ID;
	std::vector<Vertex_Buffer*> vertex_buffers;
	Index_Buffer* index_buffer;

	Vertex_Array();
	~Vertex_Array();

	void bind() const;
	void unbind() const;
	void add_vertex_buffer(const Vertex_Buffer* vertex_buffer);
	void set_index_buffer(const Index_Buffer* index_buffer);
};
