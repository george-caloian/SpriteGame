#version 330

// TODO: get color value from vertex shader
in vec3 world_pos;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float angle;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 L = normalize( light_position - world_pos);
	vec3 V = normalize( eye_position - world_pos);
	vec3 H = normalize( L + V );


	
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = 0;
	diffuse_light = material_kd * max( dot( world_normal, L ), 0 );

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = pow(max(dot(world_normal,H),0),material_shininess);
	}
	float factor = 1/pow(distance(world_pos, light_position), 2);
	float light = factor * (diffuse_light + specular_light) + ambient_light;

	// TODO: send color light output to fragment shader
	out_color = vec4(object_color * light, 1);
	
}