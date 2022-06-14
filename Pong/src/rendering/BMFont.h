#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "Texture2D.h"
#include "Shader.h"

namespace rendering {

	struct CharVertex {
		float X, Y;
		float UVX, UVY;
		float TexID; //TextureSlot
	};

	struct PageReference {
		unsigned int Page;
		std::string Name;
		Texture2D Texture;
	};

	struct CharReference {
		int X;
		int Y;
		int Width;
		int Height;
		int XOffset;
		int YOffset;
		int XAdvance;
		int PageId;
		int Channel;
	};

	class BMFont
	{
	public:
		// Data
		std::vector<PageReference> Pages;
		std::unordered_map<int, CharReference> Chars;
		// Info
		std::string Face;
		int Size;
		bool Bold;
		bool Italic;
		std::string Charset;
		bool Unicode;
		int StretchH;
		bool Smooth;
		bool AA;
		std::vector<int> Padding;
		std::vector<int> Spacing;
		bool Outline;
		// Common
		int LineHeight;
		int Base;
		int ScaleW;
		int ScaleH;
		int PageCount;
		bool Packed;
		int AlphaChnl;
		int RedChnl;
		int GreenChnl;
		int BlueChnl;
		int CharCount;

		int TextureSize;

		BMFont(const char* Filename, int textureSize);
		~BMFont();

		// Generate Quad Vertices For each char in string
		std::vector<CharVertex> GetStringVertices(std::string& line);
		std::vector<unsigned int> GetQuadIndices(unsigned int quads);
		Shader GenerateShader();
	};
}

