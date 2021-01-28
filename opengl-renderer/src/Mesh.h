#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct VertexXNU
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
};

struct Triangle_List_Info
{
	unsigned int material_index; // which material do we use to render these?
	unsigned int num_indices;    // how many vertices are in the list (must be a multiple of 3)
	unsigned int first_index;    // what is the index of the beginning of this list

	// texture map
};

struct Material
{
	std::string name;
	std::string diffuse_map;
};

struct Mesh
{
	// Imported vertex data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	std::vector<Triangle_List_Info> triangle_list_info;
	std::vector<Material> material_info;
};