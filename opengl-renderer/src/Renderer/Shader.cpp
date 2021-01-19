#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;

	vertex_shader_file.open(vertex_shader_filepath);
	fragment_shader_file.open(fragment_shader_filepath);
	std::stringstream vertex_shader_stream, fragment_shader_stream;
	vertex_shader_stream << vertex_shader_file.rdbuf();
	fragment_shader_stream << fragment_shader_file.rdbuf();
	vertex_shader_file.close();
	fragment_shader_file.close();
	std::string vertex_shader_string = vertex_shader_stream.str();
	std::string fragment_shader_string = fragment_shader_stream.str();
	const char* vertex_shader_source = vertex_shader_string.c_str();
	const char* fragment_shader_source = fragment_shader_string.c_str();

	unsigned int vertex_shader, fragment_shader;
	int success;
	char info_log[512];

	// vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	// fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}

	// shader program
	shader_ID = glCreateProgram();
	glAttachShader(shader_ID, vertex_shader);
	glAttachShader(shader_ID, fragment_shader);
	glLinkProgram(shader_ID);
	glGetProgramiv(shader_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << info_log << std::endl;
	}

	// delete shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(shader_ID);
}

void Shader::bind() const
{
	glUseProgram(shader_ID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}