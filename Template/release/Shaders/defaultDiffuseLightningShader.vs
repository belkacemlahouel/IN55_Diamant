#version 330

// ==== Variables ====
uniform float alpha;
uniform mat3 NM;
uniform mat4 MV;
uniform mat4 MVP;

in lowp vec3 color;
in mediump vec3 position;
in mediump vec3 normal;

out mediump vec3 fPos;
out mediump vec3 fNormal;

// ==== Main ====
void main(){	
	fPos = vec3(MV * vec4(position, 1.0));
	fNormal = normalize(NM*normal);
	
	gl_Position = MVP * vec4(position, 1.0);
}
