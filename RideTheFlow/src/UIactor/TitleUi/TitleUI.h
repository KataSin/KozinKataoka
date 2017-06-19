#pragma once
#include "../UIActor.h"
#include "../../actor/Player.h"
class TitleUI : public UIActor
{
public:
	enum SelectState
	{
		START,
		HELP,
		END
	};
	struct CursorState
	{
		//カーソル表示の位置
		Vector2 position;
		//どの情報か
		SelectState state;
		//画像ID
		SPRITE_ID id;
		//画像サイズ
		Vector2 textureSize;
		//ラグ情報
		bool flag = false;
	};
public:
	TitleUI(IWorld& world);
	~TitleUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//情報を取得
	std::vector<CursorState> GetCursorStates();
private:
	//現在選択されている情報
	SelectState mSelectState;
	//カーソルを重ねられる方の情報
	std::vector<CursorState> mStates;
	//現在のカーソルポジション
	Vector3 mCursorPosition;
	Vector2 mCursorSize;
	//カーソル補間系
	Vector3 mCursorVec;
	Vector3 mResCursorPos;
	//ボタン押したか
	bool mIsPushButton;

	Vector2 mButtonStartSize;
	//プッシュボタンのα値
	float mButtonAlpha;
	float mButtonAlphaCount;
	//メニューのα値
	float mMenuAlpha;
};