#version 330 core
out vec4 FragColor;

in vec2 tex_coord;
in vec4 color;

uniform sampler2D texture1;

void main()
{
	// FragColor = texture(texture1, tex_coord);
	FragColor = color;
}