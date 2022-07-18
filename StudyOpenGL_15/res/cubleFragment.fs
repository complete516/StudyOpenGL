#version 330 core
out vec4 FragColor;

uniform sampler2D cubleTexture;
in vec2 TexCoords;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main() {
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = vec4(vec3(depth),1.0);
    // FragColor = texture(cubleTexture,TexCoords);
}