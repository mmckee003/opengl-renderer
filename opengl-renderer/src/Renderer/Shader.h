#pragma once

#include <glad/glad.h>
#include <string>

struct Shader
{
	unsigned int shader_ID;

	Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
	~Shader();

	void bind() const;
	void unbind() const;
};