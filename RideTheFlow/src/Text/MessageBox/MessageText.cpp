#include "MessageText.h"
#include "../TxetRead/TextRead.h"
#include "../../input/Keyboard.h"
#include "../../time/Time.h"
MessageText::MessageText(IWorld& world, const Vector2& position, const TEXT_FILE_ID& id) :
	mTextCount(0),
	mTextPlusCount(0),
	mTextLineCount(0),
	mTextPlusCountLine(0),
	mTextPlusTimer(0.0f),
	mTextLineFlag(false)
{
	//読み込んだテキストを整理する
	for (int i = 0; i < TextRead::GetInstance().GetLine(id); i++) {
		std::vector<std::string> texts;
		std::string text;
		text = TextRead::GetInstance().GetText(id);
		//最初にlが入ったら次の行は改行とみなす
		if (text.front() == 'l') {
			//最初の文字は消す
			text.erase(text.begin());
			//消した文字を入れる
			texts.push_back(text);
			text = TextRead::GetInstance().GetText(id);
			//2行目を入れる
			texts.push_back(text);
			i++;
		}
		else {
			texts.push_back(text);
		}
		mText.push_back(texts);
	}
}

MessageText::~MessageText()
{
}

void MessageText::update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::G) &&
		mText.size() - 1 > mTextCount) {

	}

	mTextPlusTimer += Time::GetInstance().deltaTime();


	if (mTextPlusTimer >= 0.04f&&
		mText[mTextCount][mTextLineCount].size() > mTextPlusCount&&
		!mTextLineFlag) {
		mTextPlusCount += 2;
		mTextPlusTimer = 0.0f;

		//2行目があるなら2行目突入
		if (mText[mTextCount][mTextLineCount].size() <= mTextPlusCount&&
			mText[mTextCount].size() >= 2) {
			mTextLineCount++;
			mTextLineFlag = true;
		}
	}
	else if (mTextPlusTimer >= 0.04f&&
		mText[mTextCount][mTextLineCount].size() > mTextPlusCountLine&&
		mTextLineFlag) {
		mTextPlusCountLine += 2;
		mTextPlusTimer = 0.0f;
	}
}

void MessageText::draw(const Vector2& pos)
{
	//フォントサイズ変更
	SetFontSize(40);
	//2行までしかないので今回はこれだけ
	DrawFormatString(pos.x, pos.y, GetColor(0, 0, 0), mText[mTextCount].front().substr(0, mTextPlusCount).c_str());
	DrawFormatString(pos.x, pos.y+64, GetColor(0, 0, 0), mText[mTextCount].back().substr(0, mTextPlusCountLine).c_str());

}

void MessageText::SetTextCount(int count)
{
	//同じだったらり大きすぎたら返す
	if (count == mTextCount|| mText.size() <= count)return;
	mTextCount = count;
	mTextLineCount = 0;
	mTextPlusCount = 0;
	mTextPlusCountLine = 0;
	mTextPlusTimer = 0.0f;
	mTextLineFlag = false;
}

int MessageText::GetTextCount()
{
	return mTextCount;
}
