#version 330
 
uniform sampler2D texture_1;
in vec2 v_uv;


// setting float precision
precision mediump float;
layout(location = 0) out vec4 out_color;
void main()
{
    // read the fragment color from texture
	vec4 color = texture2D(texture_1, v_uv);
	if(color.a < 0.5f)
		discard;

	out_color = color;
}