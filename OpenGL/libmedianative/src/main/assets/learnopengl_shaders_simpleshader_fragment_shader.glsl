#version 300 es
in vec4 vertexColor;
out vec4 fragColor;
void main()
{
	fragColor = vertexColor;  //填充三角形区域为红色
}
