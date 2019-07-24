#version 330 core
			
layout(location = 0) out vec4 color;
//layout (location = 2) out vec2 aTexCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;
in vec4 v_FragPosLightSpace;
in vec2 v_TexCoord;

uniform vec3 light_pos;
uniform vec3 light_color = vec3(1.f);
uniform vec3 view_pos;
uniform sampler2D shadow_map;
uniform sampler2D ourTexture;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
	int type;
	vec3 direction;
	vec3 position;
	vec3 color;
	
    float intensity;

    float constant;
    float linear;
    float quadratic;
};

uniform int lightCount;
uniform Light lights[15];

vec3 calculateDirLight(Light light, vec3 normal, vec3 viewDir) {

	vec3 shadowCoords = vec3(v_FragPosLightSpace.xy, (v_FragPosLightSpace.z) / v_FragPosLightSpace.w ) * 0.5 + 0.5f;
	float bias = 0.005;
	float shadow = 1.0;	
	if ( texture( shadow_map, shadowCoords.xy ).z  <  shadowCoords.z - bias){
		shadow = 0.1;
		//shadow = 0.5;
	}

	if(shadowCoords.z > 1.f) {
		shadow = 1.0;
	}

	vec3 lightDir = normalize(light.direction);
	//diffuse part
	float diff = max(dot(normal, lightDir), 0.0);

	//specular part
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 

	//vec3 ambient = 0.25f * light.color * material.diffuse;
	vec3 ambient = 0.25f * light.color * vec3(texture(ourTexture, v_TexCoord));
	//vec3 diffuse  = light.intensity  * diff * light.color * material.diffuse;
	vec3 diffuse  = light.intensity  * diff * light.color * vec3(texture(ourTexture, v_TexCoord));
    //vec3 specular = light.intensity * spec * light.color * material.specular;
	vec3 specular = light.intensity * spec * light.color * vec3(texture(ourTexture, v_TexCoord));
    return (ambient + diffuse * shadow + specular * shadow);

}

vec3 calculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    //vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    //vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	//vec3 ambient =	light.intensity  * light.color * material.diffuse;
	vec3 ambient =	light.intensity  * light.color * vec3(texture(ourTexture, v_TexCoord));
	//vec3 diffuse  = light.intensity  * diff * light.color * material.diffuse;
	vec3 diffuse  = light.intensity  * diff * light.color * vec3(texture(ourTexture, v_TexCoord));
    //vec3 specular = light.intensity * spec * light.color * material.specular;
	vec3 specular  = light.intensity  * spec * light.color * vec3(texture(ourTexture, v_TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 


void main()
{
	float specularStrength = 0.5f;
	float ambientStrength = 0.1f;
	vec3 viewDir = normalize(view_pos - v_FragPosition);
	vec3 ambient = ambientStrength * light_color;
	vec3 lightDir = normalize(light_pos - v_FragPosition); 
	vec3 norm = normalize(v_Normal);
	vec3 reflectDir = reflect(-lightDir, norm);

	//material.diffuse = texture(ourTexture, aTexCoord);


	//vec3 result = vec3(0.f);
	//result += calculateDirLight(lights[0], norm , viewDir);
	vec3 result = vec3(0.f);
	for(int i = 0; i < lightCount; i++) {
		if(lights[i].type == 1) {
			result += calculateDirLight(lights[i], norm , viewDir);
		} else if(lights[i].type == 2) {
			result += calculatePointLight(lights[i], norm, v_FragPosition, viewDir);
		}
	}

	
	color = vec4(result, 1.0);
}