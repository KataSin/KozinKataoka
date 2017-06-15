#pragma once
#include "../UIActor.h"
#include "../../actor/Actor.h"
#include "../../actor/ActorPtr.h"
#include <vector>
class StageSelectUI :public UIActor
{
public:
	enum SelectState
	{
		BACK,
		PLAYER_NUM,
		RAUND,
		NEXT
	};
	struct CursorState
	{
		//カーソル表示の位置
		Vector2 position;
		//どの情報か
		SelectState state;
		//数字情報
		int num = 0;
		//フラグ情報
		bool flag = false;
	};
public:
	StageSelectUI(IWorld& world);
	~StageSelectUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//情報を取得
	std::vector<CursorState> GetCursorStates();
private:
	//プレイヤーたち
	std::vector<ActorPtr> mPlayers;
	//現在選択されている情報
	SelectState mSelectState;
	//カーソルを重ねられる方の情報
	std::vector<CursorState> mStates;
	//現在のカーソルポジション
	Vector2 mCursorPosition;
	//次へ行くか
	bool mIsNextFlag;
	//戻るが
	bool mIsBackFlag;
	//ボタンの中心座標
	Vector2 mButtonSize;
	//カーソル
	Vector2 mCursorSize;
	
	//カーソル補間系
	Vector3 mCursorVec;
	Vector3 mResCursorPos;
};