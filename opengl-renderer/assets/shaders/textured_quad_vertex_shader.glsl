#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec3 a_normal;
layout (location = 2) in vec2 a_uv1;

out vec3 color;
out vec2 tex_coord;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    color = a_color;
    tex_coord = a_uv1;
};