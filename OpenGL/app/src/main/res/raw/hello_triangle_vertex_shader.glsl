//顶点着色器
#version 300 es          //指定OpenGL版本号

//声明一个4维变化矩阵
uniform mat4 u_matViewProjection;
//顶点属性位置，layout声明location, in表示顶点输入变量
layout(location = 0) in vec4 a_position;
//顶点属性颜色，layout声明location, in表示顶点输入变量
layout(location = 1) in vec3 a_color;
//out表示输出颜色给片段着色器
out vec3 v_color
void main(void)
{
	//gl_Position表示最终位置
	gl_Position = u_matViewProjection * a_position;
	//顶点输入颜色赋值给v_color传递给片段着色器
	v_color = a_color;
}