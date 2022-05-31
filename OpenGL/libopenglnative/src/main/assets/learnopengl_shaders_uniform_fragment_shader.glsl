#version 300 es
layout(location = 1) uniform vec4 outColor;
out vec4 fragColor;
void main()
{
	fragColor = outColor;  //填充三角形区域为红色
}
