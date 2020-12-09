#include <vertexbuffer.h>
#include <iostream>

VertexBuffer::VertexBuffer(float* data, unsigned int size)
	: m_size(size)
{
	GLCall(glGenBuffers(1, &m_rendererID));//this is memory maybe try to find general way to adjust size?
	 
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));//state machine
	 
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));//need seperate buffers for the lines and circles

}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}



void VertexBuffer::SubData(float * data)
{
	GLCall(glNamedBufferSubData(m_rendererID, 0, m_size, data));
}

void VertexBuffer::Bind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}
