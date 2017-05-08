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
	//��s�ڂ̈ꕶ������vector�^�ŕԂ�
	std::vector <std::string>GetTextVector(TEXT_FILE_ID id);
	//���̃t�@�C�������s����Ԃ�
	int GetLine(TEXT_FILE_ID id);
	void CloseText(TEXT_FILE_ID id);
public:
	//��s�ڂ�Ԃ�
	std::string GetText(TEXT_FILE_ID id);
private:
	std::map<TEXT_FILE_ID, TextState>textId_;
};