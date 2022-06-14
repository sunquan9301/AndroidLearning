#version 300 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 transform;

out vec4 vertexColor;
out vec2 TexCoord;
void main()
{
	// 为了设置顶点着色器的输出，我们必须把位置数据赋值给预定义的gl_Position变量，它在幕后是vec4类型的。
	// 每个顶点着色器必须在gl_Position变量中输出一个位置，这个位置传递到管线下一个阶段的位置
	gl_Position = transform*vPosition;
	vertexColor = vec4(vColor.xyz,1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}