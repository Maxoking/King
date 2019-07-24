#version 330 core
			
layout(location = 0) out vec4 color;
in vec3 v_Normal;
in vec3 v_FragPosition;
in vec4 v_FragPosLightSpace;

uniform vec3 light_pos;
uniform vec3 light_color = vec3(1.f);
uniform vec3 view_pos;
uniform vec3 object_color;
uniform sampler2D shadow_map;

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

vec3 calculateDirLight(Light light, vec3 normal, vec3 viewDir, float shadow) {
	vec3 lightDir = normalize(light.direction);
	//diffuse part
	float diff = max(dot(normal, lightDir), 0.0);

	//specular part
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 

	vec3 ambient = 0.25f * light.color * material.diffuse;
	vec3 diffuse  = light.intensity  * diff * light.color * material.diffuse;
    vec3 specular = light.intensity * spec * light.color * material.specular;
    return (ambient + diffuse + specular);

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
	vec3 ambient =	light.intensity  * light.color * material.diffuse;
	vec3 diffuse  = light.intensity  * diff * light.color * material.diffuse;
    vec3 specular = light.intensity * spec * light.color * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

float calcShadow(vec4 fragPosLightSpace) {
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadow_map, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
	return shadow;
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

	//vec3 pointresult = calculateDirLight(dirlight, norm, viewDir);
	//pointresult += calculatePointLight(pointlights[0], norm, v_FragPosition, viewDir);
	//pointresult += calculatePointLight(pointlights[1], norm, v_FragPosition, viewDir);
	//vec3 pointresult = calculatePointLight(pointlights[0], norm, v_FragPosition, viewDir);

	float shadow = calcShadow(v_FragPosLightSpace);

	vec3 result = vec3(0.f);
	for(int i = 0; i < lightCount; i++) {
		if(lights[i].type == 1) {
			result += calculateDirLight(lights[i], norm , viewDir, shadow);
		} else if(lights[i].type == 2) {
			result += calculatePointLight(lights[i], norm, v_FragPosition, viewDir);
		}
	}

	//if(lights[1].type == 1) result = calculateDirLight(lights[1], norm, viewDir);
	//if(lights[1].type == 2) result = calculatePointLight(lights[1], norm, v_FragPosition, viewDir);
	//if(lights[0].type == 1) result += calculateDirLight(lights[0], norm, viewDir);

	
	color = vec4(result, 1.0);
}