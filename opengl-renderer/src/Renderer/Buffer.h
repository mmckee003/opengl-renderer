#pragma once

#include "glad\glad.h"

struct Vertex_Buffer
{
	unsigned int renderer_ID;

	Vertex_Buffer(const void* data, unsigned int size);
	~Vertex_Buffer();

	void bind() const;
	void unbind() const;
};

struct Index_Buffer
{

};