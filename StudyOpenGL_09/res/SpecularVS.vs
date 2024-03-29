#version 330 core
layout(location =  0) in vec3 aPos;
layout(location =  1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

// in vec3 Normal;  
// in vec3 FragPos;


uniform vec3 lightPos; 
uniform vec3 lightColor;
// uniform vec3 objectColor;

uniform vec3 viewPos;
out  vec3 result;

void main() {
    // gl_Position = vec4(aPos,1.0);

    vec3 FragPos = vec3(model *vec4(aPos,1.0));
    vec3 Normal = aNormal;

    gl_Position = projection * view * model *vec4(FragPos,1.0f);


    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    result = (ambient + diffuse + specular) ;


}