#include "BMFont.h"

#include <fstream>
#include <sstream>

int BMFAttrReader(std::string line, std::string attr) {
	std::string fl = attr.append("=");
	std::string op = "";
	std::string ac = "";
	int spos = line.find(fl) + fl.length();
	while (1) {
		ac = line.substr(spos + op.length(), 1);
		if (ac == " ")
			break;
		op.append(ac);
	}
	return std::stoi(op);
}

rendering::BMFont::BMFont(const char* filename)
{
	std::string file = "res/fonts/";
	file.append(filename);
	file.append(".fnt");
	std::ifstream stream(file);
	std::string line;
	while (getline(stream, line)) {
		std::string fline;
		if (line[0] == 'p') {
			fline = "page id=";
			if (line.find(fline) != std::string::npos) {
				std::string id = "";
				std::string ac = "";
				while (1) {
					ac = line.substr(line.find(fline) + fline.length(), 1);
					if (ac == " ")
						break;
					id.append(ac);
				}
				std::string imagefile = "res/fonts/";
				imagefile.append(filename).append("_").append(id).append(".png");
				pages.push_back(Texture2D(imagefile));
			}
		}
		if (line[0] == 'c') {
			if (line.find("chars count") == std::string::npos) {
				float id, x, y, width, height, xoffset, yoffset, xadvance, page;

				id			= BMFAttrReader(line, "id");
				x			= BMFAttrReader(line, "x");
				y			= BMFAttrReader(line, "y");
				width		= BMFAttrReader(line, "width");
				height		= BMFAttrReader(line, "height");
				xoffset		= BMFAttrReader(line, "xoffset");
				yoffset		= BMFAttrReader(line, "yoffset");
				xadvance	= BMFAttrReader(line, "xadvance");
				page		= BMFAttrReader(line, "page");

				Char chr {
					x, y, width, height, xoffset, yoffset, xadvance, page
				};

				chars[id] = chr;
			}
		}
	}
}

float rendering::BMFont::GetLineLength(std::string line)
{
	float r = 0;
	for (int i = 0; i < line.length(); i++) {
		if (chars.find(line[i]) != chars.end())
			r += chars[line[i]].XAdvance;
		else
			r += chars[-1].XAdvance;
	}
	return r;
}

float* rendering::BMFont::GetVertexBuffer(std::string line)
{

}

int rendering::BMFont::GetBufferSize(std::string line)
{
	return line.length() * 16;
}
