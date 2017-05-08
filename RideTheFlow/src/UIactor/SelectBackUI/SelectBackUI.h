#pragma once
#include "../UIActor.h"
#include <vector>

enum BackUiMove {
	UIMOVE_START,
	UIMOVE_END,
	UIMOVE_STOP
};
class SelectBackUI : public UIActor
{
public:
	SelectBackUI(IWorld& world);
	~SelectBackUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//移動させるid変更
	void SetSpriteID(const SPRITE_ID& id);
	//どの移動をさせるか
	void SetMove(const BackUiMove& state);
	//番号を入力
	void SetNumber(int num);
private:
	//SpriteID
	SPRITE_ID mId;
	//現在の移動状態
	BackUiMove mMove;
	//スケール
	float mScale;


	//補間用タイム
	float mLerpTimer;
	//行きよう補間
	Vector2 mStartStartPos;
	Vector2 mStartEndPos;
	//帰りよう補間
	Vector2 mEndStartPos;
	Vector2 mEndEndPos;
	//表示する数字
	int mNum;
};
