#include "Camera.h"

#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

Camera::Camera(glm::mat4& proj_matrix)
{
	projection_matrix = proj_matrix;
	// default position
	position = glm::vec3(0.0f, 0.0f, 5.0f); // back 5 units along z-axis
	yaw = -90.0f; // camarea is facing -z
	pitch = 0.0f;
}

glm::quat Camera::get_orientation()
{
	return glm::quat(glm::vec3(-pitch, -yaw, 0.0f));
}

glm::vec3 Camera::get_up_vector()
{
	return glm::rotate(get_orientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::get_forward_vector()
{
	return glm::rotate(get_orientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Camera::get_right_vector()
{
	return glm::rotate(get_orientation(), glm::vec3(1.0f, 1.0f, 0.0f));
}