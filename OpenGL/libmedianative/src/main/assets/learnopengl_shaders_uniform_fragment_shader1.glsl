#version 300 es
out vec4 fragColor;
in vec3 vertexColor;
void main()
{
	fragColor = vec4(vertexColor,1.0);  //填充三角形区域为红色
}
