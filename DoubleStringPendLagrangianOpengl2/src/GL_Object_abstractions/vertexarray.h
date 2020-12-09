#pragma once
#include "vertexbuffer.h"
# include "renderer.h"

class VertexArray {

	unsigned int m_ID;


public:


	VertexArray();

	~VertexArray();
	
	

	void Bind();
	void UnBind();
	
	void AddBuffer(const VertexBuffer& vb,unsigned int dimension);
};