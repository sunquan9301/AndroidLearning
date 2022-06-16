#version 300 es
layout(location = 0) in vec4 vPosition;
uniform mat4 mvp;
void main()
{
	gl_Position = mvp * vPosition;
}