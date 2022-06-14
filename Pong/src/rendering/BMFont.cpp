#include "BMFont.h"
#include <fstream>

std::string getWord(std::string& str) {
	std::string r = "";
	int index = 0;
	bool wordBegan = false;
	while (true) {
		if (str[index] == ' ' && wordBegan)
			break;
		if (str[index] != ' ')
		{
			wordBegan = true;
			r += str[index];
		}
		index++;
	}
	return r;
}

std::string trimWord(std::string& line) {
	int index = 0;
	bool wordBegan = false;
	bool wordEnded = false;
	while (true) {
		if (wordBegan && wordEnded && line[index] != ' ')
			break;
		else if (wordBegan && !wordEnded && line[index] == ' ')
			wordEnded = true;
		else if (!wordBegan && !wordEnded && line[index] != ' ')
			wordBegan = true;
		index++;
	}
	return line.substr(index);
}

// Assumes attr is first
std::string getAttr(std::string& line, bool quoted = false) {
	std::string r = "";
	int index = 0;
	bool equalPassed = false;
	bool quoteBegan = false;
	bool valueBegan = false;
	while (true) {
		if (index >= line.length())
			break;
		if (quoted) {
			if (equalPassed && !quoteBegan && line[index] == '"')
				quoteBegan = true;
			else if (equalPassed && quoteBegan && line[index] == '"')
				break;
			else if (equalPassed && quoteBegan) {
				valueBegan; r += line[index];
			}
			else if (line[index] == '=')
				equalPassed = true;
		}
		else {
			if (!equalPassed && line[index] == '=')
				equalPassed = true;
			else if (equalPassed && line[index] == ' ')
				break;
			else if (equalPassed) {
				r += line[index];
			}
		}
		index++;
	}
	return r;
}

int getAttrI(std::string& line) {
	std::string atr = getAttr(line);
	return std::stoi(atr);
}

std::string trimLine(std::string& line) {
	int index = 0;
	while (true) {
		if (line[index] != ' ')
			break;
		index++;
	}
	return line.substr(index);
}

std::string throwWord(std::string& line, int count = 1) {
	std::string r;
	for (int i = 0; i < count; i++) {
		r = trimWord(line);
	}
	return trimLine(r);
}

std::string throwQAttr(std::string& line) {
	int index = 0;
	bool q1found = false;
	bool q2found = false;
	while (true) {
		if (!q1found && !q2found && line[index] == '"')
			q1found = true;
		else if (q1found && !q2found && line[index] == '"')
			q2found = true;
		else if (q1found && q2found)
			break;
		index++;
	}
	std::string r = line.substr(index);
	return trimLine(r);
}

std::string trimToComma(std::string& line) {
	int index = 0;
	bool commafound = false;
	while (true) {
		if (commafound)
			break;
		if (line[index] == ',')
			commafound = true;
		index++;
	}
	return line.substr(index);
}

std::vector<int> getAttrIA(std::string& line, int count) {
	std::vector<int> values;
	std::string atrval = getAttr(line);
	int vali;
	for (int i = 0; i < (count - 1); i++) {
		std::string vals = "";
		int index = 0;
		while (true) {
			if (atrval[index] == ',')
				break;
			vals += atrval[index];
			index++;
		}
		vali = std::stoi(atrval.substr(0, index));
		values.push_back(vali);
		atrval = trimToComma(atrval);
	}
	vali = std::stoi(atrval);
	values.push_back(vali);
	return values;
}

rendering::BMFont::BMFont(const char* Filename, int textureSize)
	: TextureSize(textureSize)
{
	std::string line;
	std::ifstream stream(Filename);
	// line 0 "info"
	getline(stream, line);
	line = throwWord(line);
	Face = getAttr(line, true);
	line = throwQAttr(line);
	Size = getAttrI(line);
	line = throwWord(line);
	Bold = getAttrI(line);
	line = throwWord(line);
	Italic = getAttrI(line);
	line = throwWord(line);
	Charset = getAttr(line, true);
	line = throwQAttr(line);
	Unicode = getAttrI(line);
	line = throwWord(line);
	StretchH = getAttrI(line);
	line = throwWord(line);
	Smooth = getAttrI(line);
	line = throwWord(line);
	AA = getAttrI(line);
	line = throwWord(line);
	Padding = getAttrIA(line, 4);
	line = throwWord(line);
	Spacing = getAttrIA(line, 2);
	line = throwWord(line);
	Outline = getAttrI(line);
	// line 1 "common"
	getline(stream, line);
	line = throwWord(line);
	LineHeight = getAttrI(line);
	line = throwWord(line);
	Base = getAttrI(line);
	line = throwWord(line);
	ScaleW = getAttrI(line);
	line = throwWord(line);
	ScaleH = getAttrI(line);
	line = throwWord(line);
	PageCount = getAttrI(line);
	line = throwWord(line);
	Packed = getAttrI(line);
	line = throwWord(line);
	AlphaChnl = getAttrI(line);
	line = throwWord(line);
	RedChnl = getAttrI(line);
	line = throwWord(line);
	GreenChnl = getAttrI(line);
	line = throwWord(line);
	BlueChnl = getAttrI(line);
	// line 2 -> X "pages"
	for (int i = 0; i < PageCount; i++) {
		getline(stream, line);
		line = throwWord(line);
		int p = getAttrI(line);
		line = throwWord(line);
		std::string f = getAttr(line, true);
		Texture2D t("res/fonts/" + f);
		PageReference r{ p, f , t };
		Pages.push_back(r);
	}
	// line X+1 "char count"
	getline(stream, line);
	line = throwWord(line);
	CharCount = getAttrI(line);
	// line X+2 -> end "chars"
	for (int i = 0; i < CharCount; i++) {
		getline(stream, line);
		line = throwWord(line);
		int id = getAttrI(line);
		line = throwWord(line);
		int x = getAttrI(line);
		line = throwWord(line);
		int y = getAttrI(line);
		line = throwWord(line);
		int width = getAttrI(line);
		line = throwWord(line);
		int height = getAttrI(line);
		line = throwWord(line);
		int xoffset = getAttrI(line);
		line = throwWord(line);
		int yoffset = getAttrI(line);
		line = throwWord(line);
		int xadvance = getAttrI(line);
		line = throwWord(line);
		int page = getAttrI(line);
		line = throwWord(line);
		int chnl = getAttrI(line);
		CharReference r{ x, y, width, height, xoffset, yoffset, xadvance, page, chnl };
		Chars[id] = r;
	}
}

rendering::BMFont::~BMFont()
{
}

std::vector<rendering::CharVertex> rendering::BMFont::GetStringVertices(std::string& line)
{
	std::vector<CharVertex> vertices;
	float XAdvance = 0.0f;
	float YAdvance = 0.0f;
	int index = 0;
	int length = line.length();
	while (index < length) {
		switch (line[index]) {
		case '\n':
			YAdvance += (float)LineHeight;
			XAdvance = 0.0f;
			break;
		default:
			CharReference ref = Chars[line[index]];
			CharVertex vert0{
				XAdvance + ref.XOffset,
				YAdvance + ref.YOffset,
				(float)ref.X / (float)TextureSize,
				(float)ref.Y / (float)TextureSize,
				ref.PageId
			};
			CharVertex vert1{
				XAdvance + ref.XOffset + ref.Width,
				YAdvance + ref.YOffset,
				(float)(ref.X + ref.Width) / (float)TextureSize,
				(float)ref.Y / (float)TextureSize,
				ref.PageId
			};
			CharVertex vert2{
				XAdvance + ref.XOffset,
				YAdvance + ref.YOffset + ref.Height,
				(float)ref.X / (float)TextureSize,
				(float)(ref.Y + ref.Height) / (float)TextureSize,
				ref.PageId
			};
			CharVertex vert3{
				XAdvance + ref.XOffset + ref.Width,
				YAdvance + ref.YOffset + ref.Height,
				(float)(ref.X + ref.Width) / (float)TextureSize,
				(float)(ref.Y + ref.Height) / (float)TextureSize,
				ref.PageId
			};
			vertices.push_back(vert0);
			vertices.push_back(vert1);
			vertices.push_back(vert2);
			vertices.push_back(vert3);
			break;
		}
		index++;
	}
	return vertices;
}

std::vector<unsigned int> rendering::BMFont::GetQuadIndices(unsigned int quads)
{
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < quads; i++) {
		indices.push_back((i * 4) + 0);
		indices.push_back((i * 4) + 1);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 3);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 1);
	}
	return indices;
}

#include "glad/glad.h"
#include <sstream>

rendering::Shader rendering::BMFont::GenerateShader()
{
	const char* vertexSource = 
		"#version 460\n"
		"\n"
		"layout(location = 0) in vec2 posit;\n"
		"layout(location = 1) in vec2 texCo;\n"
		"layout(location = 2) in float texId;\n"
		"\n"
		"out vec2 v_texCo;\n"
		"out float v_texId;\n"
		"\n"
		"uniform mat4 view;\n"
		"uniform vec2 model;\n"
		"\n"
		"void main() {\n"
		"    gl_Position = view * vec4(posit.x + model.x, posit.y + model.y, 0.0f, 1.0f);\n"
		"};\n";

	std::stringstream fragmentStream;
	fragmentStream
		<< "#version 460\n"
		<< "\n"
		<< "in vec2 v_texCo;\n"
		<< "in float v_texId;\n"
		<< "\n"
		<< "out vec4 fragColour;\n"
		<< "\n"
		<< "uniform sampler2D u_Texture";
	if (PageCount == 1)
		fragmentStream << ';';
	else {
		fragmentStream 
			<< "s[" 
			<< PageCount 
			<< "];\n";
	}
	fragmentStream
		<< "uniform vec4 u_textColour;\n"
		<< "\n"
		<< "void main() {\n"
		<< "    int txId = int(v_texId);\n"
		<< "    \n"
		<< "    fragColour = texture(u_Texture" << ((PageCount == 1) ? "" : "s[txId]")
		<< ", v_texCo) * u_textColour;\n"
		<< "    \n"
		<< "    \n"
		<< "};\n";

	std::string fragmentString = fragmentStream.str();
	const char* fragmentSource = fragmentString.c_str();

	unsigned int programme = glCreateProgram();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	glAttachShader(programme, vertexShader);
	glAttachShader(programme, fragmentShader);

	glLinkProgram(programme);
	glValidateProgram(programme);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return Shader(programme);
}
