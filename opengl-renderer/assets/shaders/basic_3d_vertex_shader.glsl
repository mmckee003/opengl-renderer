#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_tex_coord;

out vec2 tex_coord;
out vec4 color;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * world * vec4(a_pos, 1.0f);
	tex_coord = vec2(a_tex_coord.x, a_tex_coord.y);
	color = vec4(a_color, 1.0f);
}