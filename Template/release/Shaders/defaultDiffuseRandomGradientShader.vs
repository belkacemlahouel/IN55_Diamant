#version 140

uniform mat4 MVP;
in vec3 position;
in vec3 color;
out vec4 fColor;

void main()
{
	vec4 p = MVP * vec4(position, 1.0);
	gl_Position = p;
	fColor = abs(sin(vec4(position, 1.0)));
}
