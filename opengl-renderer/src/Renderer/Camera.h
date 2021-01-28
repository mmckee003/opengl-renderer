#pragma once

#include <glm/glm.hpp>

struct Camera
{
	glm::vec3 position;
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	float pitch;
	float yaw;

	Camera(glm::mat4& proj_matrix);
	glm::quat get_orientation();
	glm::vec3 get_up_vector();
	glm::vec3 get_forward_vector();
	glm::vec3 get_right_vector();
};
