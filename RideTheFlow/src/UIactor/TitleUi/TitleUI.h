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
	};
public:
	TitleUI(IWorld& world);
	~TitleUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	//現在選択されている情報
	SelectState mSelectState;
	//カーソルを重ねられる方の情報
	std::vector<CursorState> mStates;
	//現在のカーソルポジション
	Vector2 mCursorPosition;
};