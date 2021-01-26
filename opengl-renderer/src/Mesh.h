#pragma once

#include <glm/glm.hpp>
#include <vector>

struct VertexXCNU
{
	float position[3];
	float color[3];
	int normal[3];
	int UV1[2];
};

struct Triangle_List_Info
{
	unsigned int material_index; // which material do we use to render these?
	unsigned int num_indices;    // how many vertices are in the list (must be a multiple of 3)
	unsigned int first_index;    // what is the index of the beginning of this list

	// texture map
};

struct Mesh
{
	// Imported vertex data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;


};