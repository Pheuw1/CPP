#pragma once
#include <renderer.h>
class IndexBuffer {

	unsigned int m_rendererID;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int GetCount();
};