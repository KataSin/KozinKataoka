#include "TitleUI.h"
#include "../../world/IWorld.h"
#include "../../input/Keyboard.h"
#include "../../input/GamePad.h"
#include "../../math/Math.h"
#include"../../Def.h"
TitleUI::TitleUI(IWorld & world):
	UIActor(world),
	mSelectState(SelectState::START)
{
	parameter.isDead = false;
	//スタート
	{
		CursorState state;
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 400.0f);
		state.state = SelectState::START;
	}
	//ヘルプ
	{
		CursorState state;
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 460.0f);
		state.state = SelectState::HELP;
	}
	//エンド
	{
		CursorState state;
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 520.0f);
		state.state = SelectState::END;
	}

}

TitleUI::~TitleUI()
{
}

void TitleUI::Update(PLAYER_NUMBER playerNumber)
{
	//カーソル移動
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
		mSelectState = (SelectState)((int)mSelectState + 1);
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
		mSelectState = (SelectState)((int)mSelectState - 1);
	mSelectState = (SelectState)Math::Clamp((int)mSelectState, 0, mStates.size() - 1);



}

void TitleUI::Draw() const
{
	
}
