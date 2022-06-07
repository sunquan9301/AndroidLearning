#version 300 es
// 表示OpenGL ES着色器语言V3.00

// 使用in关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)。
// 声明一个输入属性数组：一个名为vPosition的4分量向量
// 图形编程中会使用向量,因此线性代数很重要
layout(location = 0) in vec4 vPosition;
void main()
{
	//gl_Position是内置变量，更多的内置变量可参考：
	//https://www.khronos.org/files/opengles32-quick-reference-card.pdf
	gl_Position = vPosition;
}