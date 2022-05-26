#pragma once

#include <vector>

#include "VertexBufferElement.h"

namespace rendering {
	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout();
		void PushFloat(unsigned int count);
		void PushCount(unsigned int count);
		void PushByte(unsigned int count);

		inline const std::vector< VertexBufferElement> GetElements() const& { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }
	};
}
