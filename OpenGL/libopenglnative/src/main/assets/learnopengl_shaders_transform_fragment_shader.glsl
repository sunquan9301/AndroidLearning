#version 300 es
in vec4 vertexColor;
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture;

void main()
{
	FragColor = texture(texture, TexCoord);
}
