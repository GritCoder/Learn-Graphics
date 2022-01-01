#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    // 只使用了漫反射贴图    
    FragColor = texture(texture_diffuse1, TexCoords);
}
