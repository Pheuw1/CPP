#version 330 core
layout(location = 0) in vec4 position;
void main()
{
	gl_Position = position;
}

// use Shader Storage Buffer Object: can contain aribtraty data and is manipulated in c-like way

// i want to use the compute shader for updating position and velocity buffers
//Opengl rendering will read posistion buffer