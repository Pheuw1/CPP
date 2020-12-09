#include "Indexbuffer.h"
#include <renderer.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{

	GLCall(glGenBuffers(1, &m_rendererID));//this is memory maybe try to find general way to adjust size?
	 
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));//state machine

	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(GLuint), data, GL_STATIC_DRAW));//need seperate buffers for the lines and circle
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::Bind() const 
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

unsigned int IndexBuffer::GetCount() { return m_count; }