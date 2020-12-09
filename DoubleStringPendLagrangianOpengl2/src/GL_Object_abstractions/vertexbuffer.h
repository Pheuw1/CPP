#pragma once
#include <renderer.h>

class VertexBuffer {
	GLuint m_rendererID;
public:

	unsigned int m_size;

	VertexBuffer(float* data, unsigned int size);
	~VertexBuffer();
	void SubData(float* data);
	void Bind() const;
	void UnBind() const;


};