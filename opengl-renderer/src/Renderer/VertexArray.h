#pragma once

#include "Buffer.h"

#include <vector>

struct Vertex_Array
{
	unsigned int renderer_ID;
	Vertex_Buffer* vertex_buffer;
	Index_Buffer* index_buffer;

	Vertex_Array();
	~Vertex_Array();

	void bind() const;
	void unbind() const;
	void set_vertex_buffer(Vertex_Buffer* vertex_buffer);
	void set_index_buffer(Index_Buffer* index_buffer);
};
