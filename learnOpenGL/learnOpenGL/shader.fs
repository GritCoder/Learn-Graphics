//#version 330 core
//out vec4 FragColor;
//
//in vec3 ourColor;
//in vec2 TexCoord;
//
//// texture sampler
//uniform sampler2D texture1;
//uniform float delay;
//
//void main()
//{
//    // sRGB描述文件 颜色应该按如下方式操作
//    float a = texture(texture1, TexCoord).a;
//    vec3 color = texture(texture1, TexCoord).rgb;
//
////    FragColor = vec4(change_rgb(color, base_time), change_alpha(a, base_time));
////    std::cout<<deltaTimes;
//    FragColor = vec4(color * delay, a * delay);
//
//}
//
//


// 纹理坐标映射demo          
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
}
