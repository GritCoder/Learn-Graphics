//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;
//uniform mat4 model;
//out vec3 ourColor;
//out vec2 TexCoord;
//void main()
//{
//    gl_Position = model * vec4(aPos, 1.0);
//    ourColor = aColor;
//    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
//}


// 纹理坐标映射demo
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
