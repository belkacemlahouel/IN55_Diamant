#version 150

// ==== Structures ====
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
uniform mat4 V;
uniform mat3 NM;
uniform mat4 MV;
uniform mat4 MVP;

uniform LightSource light;
uniform Material material;

in vec3 color;
in vec3 position;
in vec4 normal;

out vec4 fColor;


// ==== Lighting functions ====
void DirectionalLight(in vec3 V, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	
	vec3 halfway_vector = normalize(V+light.posDir.xyz);
	nDotL = max(0.0, dot(normal, normalize(vec3(light.posDir))));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else{
		nDotH = max(0.0, dot(normal, halfway_vector));
		powerFactor = pow(nDotH, 4*material.shininess);
	}
	
	ambient += light.ambient;
	diffuse += light.diffuse * nDotL;
	specular += light.specular * powerFactor;
}
void PointLight(in vec3 V, in vec3 sp, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	float attenuation;
	float distance;
	vec3 L;
	vec3 halfway_vector;
	
	L = light.posDir.xyz;
	L = L - sp;
	distance = length(L);
	L = normalize(L);
	attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * distance * distance);
	
	halfway_vector = normalize(L + V);
	nDotL = max(0.0, dot(normal, L));
	nDotH = max(0.0, dot(normal, halfway_vector));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else					powerFactor = pow(nDotH, material.shininess);
		
	ambient += light.ambient;
	diffuse += light.diffuse * nDotL * attenuation;
	specular += light.specular * powerFactor * attenuation;
}
void SpotLight(in vec3 V, in vec3 sp, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular){
	float nDotL;
	float nDotH;
	float powerFactor;
	float spotDot; // cosine of angle between spotlight
	float spotAttenuation;
	float attenuation;
	float distance;
	vec3 L;
	vec3 halfway_vector;
	
	L = light.posDir.xyz;
	L = L - sp;
	distance = length(L);
	L = normalize(L);
	attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * distance * distance);
	
	float cos_cutoff;	
	// See if point on surface is inside the cone of illumination
	spotDot = dot(-L, normalize(light.spotDirection));
	cos_cutoff = cos(light.spotCutoff);
	
	if (spotDot < cos_cutoff)		spotAttenuation = 0.0;
	else							spotAttenuation = pow(spotDot, light.spotExponent);
		
	attenuation *= spotAttenuation;
	halfway_vector = normalize(L + V);
	nDotL = max(0.0, dot(normal, L));
	nDotH = max(0.0, dot(normal, halfway_vector));
	
	if (nDotL == 0.0)		powerFactor = 0.0;
	else					powerFactor = pow(nDotH, material.shininess);
		
	ambient += light.ambient;
	diffuse += light.diffuse * nDotL * attenuation;
	specular += light.specular * powerFactor * attenuation;
}


// ==== Main ====
void main(){
	vec3 sp = vec3(MV*vec4(position, 1.0));
	vec3 V = -normalize(sp);
	vec3 unit_normal = normalize(NM*normal.xyz);
	
	vec4 ambiant = vec4(0.0, 0.0, 0.0, 0.0); 
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0); 
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	
	if (light.posDir.w == 0.0)   
		DirectionalLight(V, unit_normal, ambiant, diffuse, specular);
	else if (light.spotCutoff == 180.0)
		PointLight(V, sp, unit_normal, ambiant, diffuse, specular);
	else
		SpotLight(V, sp, unit_normal, ambiant, diffuse, specular);			
	
	gl_Position = MVP * vec4(position, 1.0);
	fColor = ambiant + diffuse + specular;
}
