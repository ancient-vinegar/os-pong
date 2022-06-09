#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Texture2D.h"

namespace rendering {

	struct Char {
	public:
		float X;
		float Y;
		float Width;
		float Height;
		float XOffset;
		float YOffset;
		float XAdvance;
		float Page;
	};

	class BMFont
	{
	private:
		std::unordered_map<int, Char> chars;
		std::vector<Texture2D> pages;
	public:
		BMFont(const char* filename);

		float GetLineLength(std::string line);
		float* GetVertexBuffer(std::string line);
		int GetBufferSize(std::string line);
	};
}

