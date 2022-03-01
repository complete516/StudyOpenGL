#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec2 TexCoord2;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    // FragColor = vec4(ourColor,1.0); //vec4(0.0,0.0,0.0,1.0);
    // 修改片段着色器，仅让笑脸图案朝另一个方向看 begin
    // vec4 v2 = texture(texture2,vec2(1.0-TexCoord.x,TexCoord.y));
    //end

    vec4 v2 = texture(texture2,TexCoord);

    FragColor = mix(texture(texture1,TexCoord),v2,0.2);// *vec4(ourColor,1.0);
}