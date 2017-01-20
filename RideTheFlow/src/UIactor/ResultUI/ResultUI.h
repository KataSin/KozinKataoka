#pragma once
#include "../UIActor.h"
#include "../../GamePlayManager/GamePlayManager.h"
#include <vector>
class ResultUI : public UIActor
{
public:
	ResultUI(IWorld& world,GamePlayManager& gameManager,PLAYER_NUMBER winPlayer );
	~ResultUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//結果テクスチャサイズ
	Vector2 mTexSize;
	//トロフィーをあげるポジション
	Vector2 mTrophyPos;
	//全トロフィーのポジション
	Vector2 mTrophyAllPos;
	//勝ち数
	std::map<PLAYER_NUMBER, int> mWinCount;
	//勝ったプレイヤー
	PLAYER_NUMBER mWinPlayer;
	//結果α
	float mAlpha;
	//トロフィーα
	float mTrophyAlpha;
	//トロフィーサイズ
	float mSize;
};