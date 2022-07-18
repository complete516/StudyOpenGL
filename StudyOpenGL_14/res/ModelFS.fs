#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specualr1;

struct Light{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 diffuse;    

} ;

uniform Light light;


void main() {
    
    vec3 diffuse = texture(texture_diffuse1,TexCoords).rgb;

    float distance = length(light.position-FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 specualr = texture(texture_specualr1,TexCoords).rgb;

    diffuse *= attenuation;
    specualr *= attenuation;
    
    vec3 result = diffuse + specualr ;

    FragColor = vec4(result,1.0);
}