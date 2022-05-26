#include "VertexArray.h"

#include <glad/glad.h>

rendering::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

rendering::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void rendering::VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void rendering::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void rendering::VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& elements = vertexBufferLayout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vertexBufferLayout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
