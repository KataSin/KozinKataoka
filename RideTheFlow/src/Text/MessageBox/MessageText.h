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

	//何行目を再生するか
	void SetTextCount(int count);
	//何行目を再生しているか
	int GetTextCount();
private:
	//どこまでテキストが行ったか
	int mTextCount;
	//どんどん文字が出てくる
	int mTextPlusCount;
	//2行目版
	int mTextPlusCountLine;
	//どんどん文字が出てくる時間
	float mTextPlusTimer;
	//どの行を再生しているか
	int mTextLineCount;
	//2行目かどうか
	bool mTextLineFlag;
	Vector2 mPosition;
	Text mText;
};