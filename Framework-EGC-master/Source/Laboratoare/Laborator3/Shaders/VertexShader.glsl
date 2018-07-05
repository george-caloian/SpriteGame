#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties

out vec2 texcoord;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader

	texcoord = v_texture_coord;

	gl_Position = vec4(v_position, 1.0);
}
