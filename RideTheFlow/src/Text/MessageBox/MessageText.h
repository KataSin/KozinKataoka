#pragma once

#include "../../actor/Actor.h"
#include "../../world/IWorld.h"
#include <string>
#include <vector>
class MessageText {
public:
	typedef std::vector<std::vector<std::string>> Text;

public:
	MessageText(IWorld& world,const Vector2& position,const TEXT_FILE_ID& id);
	~MessageText();
	void update();
	void draw(const Vector2& pos);

	//���s�ڂ��Đ����邩
	void SetTextCount(int count);
	//���s�ڂ��Đ����Ă��邩
	int GetTextCount();
private:
	//�ǂ��܂Ńe�L�X�g���s������
	int mTextCount;
	//�ǂ�ǂ񕶎����o�Ă���
	int mTextPlusCount;
	//2�s�ڔ�
	int mTextPlusCountLine;
	//�ǂ�ǂ񕶎����o�Ă��鎞��
	float mTextPlusTimer;
	//�ǂ̍s���Đ����Ă��邩
	int mTextLineCount;
	//2�s�ڂ��ǂ���
	bool mTextLineFlag;
	Vector2 mPosition;
	Text mText;
};