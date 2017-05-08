#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "../../actor/ID.h"
#include <DxLib.h>
#include <string>
class TextRead {
	struct TextState
	{
		int handle;
		int lineNum;
	};
public:
	static TextRead& GetInstance();
	~TextRead();
	void ReadTxt(TEXT_FILE_ID id,char* pas,int line);
	//一行目の一文字ずつvector型で返す
	std::vector <std::string>GetTextVector(TEXT_FILE_ID id);
	//そのファイルが何行かを返す
	int GetLine(TEXT_FILE_ID id);
	void CloseText(TEXT_FILE_ID id);
public:
	//一行目を返す
	std::string GetText(TEXT_FILE_ID id);
private:
	std::map<TEXT_FILE_ID, TextState>textId_;
};