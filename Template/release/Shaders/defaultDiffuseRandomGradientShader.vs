#version 140

uniform float alpha;
uniform mat4 NP;
uniform mat4 MV;
uniform mat4 MVP;

in vec3 color;
in vec3 position;
in vec4 normal;

out vec4 fColor;

void main()
{
	vec4 p = MVP * vec4(position, 1.0);
	gl_Position = p;
	fColor = vec4(abs(sin(position)), alpha);
}
