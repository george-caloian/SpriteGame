#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 a_uv;
layout(location = 3) in vec3 v_color;

// array that contains information on
// sprite


uniform vec4 sprite;
uniform int direction;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
out vec2 v_uv;
void main()
{
    
	vec2 textureSize;
	textureSize.x = 8115;
	textureSize.y = 2916;

	if (direction == -1)
		v_uv.x = ((1.00 - a_uv.x) * sprite.z) / textureSize.x + sprite.x / textureSize.x;
	else
		v_uv.x = (a_uv.x * sprite.z) / textureSize.x + sprite.x / textureSize.x;
	v_uv.y = ((1.00 - a_uv.y) * sprite.w) / textureSize.y + sprite.y / textureSize.y;
	
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
    
}