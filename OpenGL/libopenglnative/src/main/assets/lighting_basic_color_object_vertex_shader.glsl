#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 3) in vec3 Normal;
out vec3 FragPos;
out vec3 NormalPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	NormalPos = Normal;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}