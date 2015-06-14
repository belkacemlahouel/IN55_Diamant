#version 330

// ==== Structures ====
struct LightSource{
	mediump vec4 posDir;
	
	lowp vec4 ambient;
	lowp vec4 diffuse;
	lowp vec4 specular;
	
	lowp float constantAttenuation;
	lowp float linearAttenuation;
	lowp float quadraticAttenuation;
	
	vec3 spotDirection;
	float spotCutoff;
	float spotExponent;
};
struct Material{
	lowp vec4 ambient;
	lowp vec4 diffuse;
	lowp vec4 specular;
	lowp float shininess;
};

// ==== Variables ====
uniform mat4 V;

uniform lowp float alpha;
uniform LightSource light;
uniform Material material;

in mediump vec3 fPos;
in mediump vec3 fNormal;

out lowp vec4 fragColor;

// ==== Main ====
void main()
{ 
    mediump vec3 l = normalize(vec3(V * light.posDir) - fPos);
    mediump vec3 e = normalize(-fPos);
	mediump vec3 r = normalize(-reflect(l,fNormal));
		
	lowp vec4 ambient = light.ambient;
	lowp vec4 diffuse = clamp(light.diffuse * max(dot(fNormal,l), 0.0), 0.0, 1.0);
	lowp vec4 specular = clamp(light.specular * pow(max(dot(r,e), 0.0), 0.3*material.shininess), 0, 1.0);
	
	fragColor = material.ambient + ambient + diffuse + specular;
	fragColor.w = fragColor.w * alpha;
}
