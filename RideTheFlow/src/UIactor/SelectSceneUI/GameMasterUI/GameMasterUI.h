#pragma once
#include "../../UIActor.h"
#include <vector>

class AnimetionClass;
class MessageText;
class GameMasterUI : public UIActor
{
public:
	GameMasterUI(IWorld& world);
	~GameMasterUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//何番目を喋らせるか
	void SetMasterText(int num);
	//何番目を喋っているか
	int GetMasterText();
private:
	//テキストの後ろのある画像座標
	Vector2 mTextBackPos;
	//テキスト後ろの画像サイズ
	Vector2 mTextBackSize;
	//メッセージ
	MessageText* mMessageText;
	//ゲームマスターがどこを喋っているか
	int mMessageCount;
	AnimetionClass* mGameMasterAnim;
};
