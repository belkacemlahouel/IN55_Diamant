#version 140

// ==== Structures ====
struct LightSources{
	int nbrLights;
	LightSource source[2];
};
struct LightSource{
	vec4 posDir;
	
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	vec3 spotDirection;
	float spotCutoff;
	float spotExponent;
};
struct Material{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};


// ==== Variables ====
uniform float alpha;
uniform mat3 NM;
uniform mat4 MV;
uniform mat4 MVP;

uniform LightSources lights;
uniform LightSource light;
uniform Material material;

in vec3 color;
in vec3 position;
in vec4 normal;

out vec4 fColor;


// ==== Main ====
void main(){
	vec3 sp = vec3(MV*position);
	vec3 V = -normalize(sp);
	vec3 unit_normal = normalize(NM*normal.xyz);
	
	vec4 ambiant = vec4(0.0); 
	vec4 diffuse = vec4(0.0); 
	vec4 specular = vec4(0.0);
	
	for(int i=0; i<lights.nbrLights; i++){
		if (lights.source[i].posDir.w == 0.0)   
			DirectionalLight(i, V, unit_normal, ambiant, diffuse, specular);
		else if (lights.source[i].spotCutoff == 180.0)
			PointLight(i, V, sp, unit_normal, ambiant, diffuse, specular);
		else
			SpotLight(i, V, sp, unit_normal, ambiant, diffuse, specular);			
	}
	
	fcolor = fcolor + ambiant + diffuse + specular;
}

// ==== Lighting functions ====
void DirectionalLight(in int i, in vec3 V, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	
	vec3 halfway_vector = normalize(V+lights.source[i].posDir.xyz);
	nDotL = max(0.0, dot(normal, normalize(vec3(lights.source[i].posDir))));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else{
		nDotH = max(0.0, dot(normal, halfway_vector));
		powerFactor = pow(nDotH, 4*material.shininess);
	}
	
	ambient += lights.source[i].ambient;
	diffuse += lights.source[i].diffuse * nDotL;
	specular += lights.source[i].specular * powerFactor;
}
void PointLight(in int i, in vec3 V, in vec3 sp, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	float attenuation;
	float distance;
	vec3 L;
	vec3 halfway_vector;
	
	L = lights.source[i].position.xyz - sp;
	distance = length(L);
	L = normalize(L);
	attenuation = 1.0 / (lights.source[i].constantAttenuation + lights.source[i].linearAttenuation * distance + lights.source[i].quadraticAttenuation * distance * distance);
	
	halfway_vector = normalize(L + V);
	nDotL = max(0.0, dot(normal, L));
	nDotH = max(0.0, dot(normal, halfway_vector));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else					powerFactor = pow(nDotH, material.shininess);
		
	ambient += lights.source[i].ambient;
	diffuse += lights.source[i].diffuse * nDotL * attenuation;
	specular += lights.source[i].specular * powerFactor * attenuation;
}
void SpotLight(in int i, in vec3 V, in vec3 sp, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	float spotDot; // cosine of angle between spotlight
	float spotAttenuation;
	float attenuation;
	float distance;
	vec3 L;
	vec3 halfway_vector;
	
	L = lights.source[i].position.xyz – sp;
	distance = length(L);
	L = normalize(L);
	attenuation = 1.0 / (lights.source[i].constantAttenuation + lights.source[i].linearAttenuation * distance + lights.source[i].quadraticAttenuation * distance * distance);
	
	float cos_cutoff;	
	// See if point on surface is inside the cone of illumination
	spotDot = dot(-L, normalize(lights.source[i].spotDirection));
	cos_cutoff = cos(lights.source[i].spotCutoff);
	
	if (spotDot < cos_cutoff)		spotAttenuation = 0.0;
	else							spotAttenuation = pow(spotDot, lights.source[i].spotExponent);
		
	attenuation *= spotAttenuation;
	halfway_vector = normalize(L + V);
	nDotL = max(0.0, dot(normal, L));
	nDotH = max(0.0, dot(normal, halfway_vector));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else					powerFactor = pow(nDotH, material.shininess);
		
	ambient += lights.source[i].ambient;
	diffuse += lights.source[i].diffuse * nDotL * attenuation;
	specular += lights.source[i].specular * powerFactor * attenuation;
}
