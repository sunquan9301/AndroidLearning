#version 300 es
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}