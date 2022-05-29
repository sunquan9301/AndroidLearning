#version 300 es
out vec4 fragColor;
in vec4 vertexColor;
void main()
{
	fragColor = vertexColor;  //填充三角形区域为红色
}
