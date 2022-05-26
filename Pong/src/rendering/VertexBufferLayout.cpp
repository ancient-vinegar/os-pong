#include "VertexBufferLayout.h"

#include <glad/glad.h>

rendering::VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0) { }

void rendering::VertexBufferLayout::PushFloat(unsigned int count)
{
	VertexBufferElement e;
	e.type = GL_FLOAT;
	e.count = count;
	e.normalized = GL_FALSE;
	m_Elements.push_back(e);
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

void rendering::VertexBufferLayout::PushCount(unsigned int count)
{
	VertexBufferElement e;
	e.type = GL_UNSIGNED_INT;
	e.count = count;
	e.normalized = GL_FALSE;
	m_Elements.push_back(e);
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

void rendering::VertexBufferLayout::PushByte(unsigned int count)
{
	VertexBufferElement e;
	e.type = GL_UNSIGNED_BYTE;
	e.count = count;
	e.normalized = GL_TRUE;
	m_Elements.push_back(e);
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
