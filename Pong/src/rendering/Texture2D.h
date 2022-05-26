#pragma once

#include <string>

namespace rendering {
	class Texture2D
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		Texture2D(const std::string& filePath);
		~Texture2D();

		void Bind(unsigned int Slot = 0) const;
		void UnBind();

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
	};
}
