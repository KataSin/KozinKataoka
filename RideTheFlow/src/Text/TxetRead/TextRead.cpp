#include "TextRead.h"
#include "TextRead.h"


TextRead & TextRead::GetInstance()
{
	static TextRead instance;
	return instance;
}


TextRead::~TextRead()
{
}


void TextRead::ReadTxt(TEXT_FILE_ID id, char * pas,int line)
{
	textId_[id].handle = FileRead_open(pas);
	textId_[id].lineNum = line;
}

std::string TextRead::GetText(TEXT_FILE_ID id)
{
	char text[256];
	std::string textString;
	FileRead_gets(text, 256, textId_[id].handle);
	textString = text;
	return textString;
}

std::vector<std::string> TextRead::GetTextVector(TEXT_FILE_ID id)
{
	char text[256];
	std::string textString;
	std::vector<std::string> textVec;
	FileRead_gets(text, 256, textId_[id].handle);
	textString = text;
	for (int i = 0; i < textString.size(); i++) {
		//•ÏŠ·—p
		std::string a;
		a = textString[i];
		textVec.push_back(a);
	}
	return textVec;
}

int TextRead::GetLine(TEXT_FILE_ID id)
{
	return textId_[id].lineNum;
}

void TextRead::CloseText(TEXT_FILE_ID id)
{
	FileRead_close(textId_[id].handle);
}
