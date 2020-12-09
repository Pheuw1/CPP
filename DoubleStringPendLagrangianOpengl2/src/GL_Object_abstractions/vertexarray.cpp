#include "vertexarray.h"



VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ID));

}


VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(0));
	GLCall(glBindVertexArray(m_ID));

}

void VertexArray::UnBind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, unsigned int dimension)
{
	Bind();
	vb.Bind();
	GLCall(glEnableVertexArrayAttrib(m_ID, 0));
	GLCall(glVertexAttribPointer(0,dimension, GL_FLOAT, GL_FALSE, dimension*sizeof(float), nullptr));
	UnBind();
	vb.UnBind();
}