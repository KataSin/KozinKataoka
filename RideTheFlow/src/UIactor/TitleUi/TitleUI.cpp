#include "TitleUI.h"
#include "../../world/IWorld.h"
#include "../../input/Keyboard.h"
#include "../../input/GamePad.h"
#include "../../math/Math.h"
#include"../../Def.h"
#include "../../actor/RotateStage/RotateStage.h"
#include "../../time/Time.h"
TitleUI::TitleUI(IWorld & world):
	UIActor(world),
	mSelectState(SelectState::START),
	mIsPushButton(false),
	mButtonAlpha(0.0f),
	mButtonAlphaCount(0.0f),
	mMenuAlpha(0.0f)
{
	parameter.isDead = false;
	//スタート
	{
		CursorState state;
		state.id = SPRITE_ID::GAME_START_BUTTON_SPRITE;
		state.textureSize = Sprite::GetInstance().GetSizeVector(state.id);
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 400.0f);
		state.state = SelectState::START;
		mStates.push_back(state);
	}
	//ヘルプ
	{
		CursorState state;
		state.id = SPRITE_ID::HELP_BUTTON_SPRITE;
		state.textureSize = Sprite::GetInstance().GetSizeVector(state.id);
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 520.0f);
		state.state = SelectState::HELP;
		mStates.push_back(state);
	}
	//エンド
	{
		CursorState state;
		state.id = SPRITE_ID::END_BUTTON_SPRITE;		
		state.textureSize = Sprite::GetInstance().GetSizeVector(state.id);
		state.position = Vector2(WINDOW_WIDTH / 2.0f, 640.0f);
		state.state = SelectState::END;
		mStates.push_back(state);
	}

	//補間関係
	mResCursorPos = Vector3(mStates[mSelectState].position.x, mStates[mSelectState].position.y, 0.0f);
	mCursorPosition = mResCursorPos;
	mCursorVec = Vector3::Zero;

	mCursorSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::TITLE_CUROSR_SPRITE);

	mButtonStartSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::BUTTON_START_SPRITE);

	//回るステージ追加
	world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<RotateStage>(world, Vector3::Zero));
}

TitleUI::~TitleUI()
{
}

void TitleUI::Update(PLAYER_NUMBER playerNumber)
{
	if (mIsPushButton) {
		mMenuAlpha += Time::GetInstance().deltaTime();
		mButtonAlpha -= Time::GetInstance().deltaTime();

		//カーソル移動
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
			mSelectState = (SelectState)((int)mSelectState + 1);
		else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
			mSelectState = (SelectState)((int)mSelectState - 1);
		mSelectState = (SelectState)Math::Clamp((int)mSelectState, 0, mStates.size() - 1);
		//カーソルがどこに行くか
		for (auto& i : mStates) {
			if (i.state == mSelectState) {
				mResCursorPos = Vector3(i.position.x, i.position.y, 0.0f);
				if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) ||
					Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
					i.flag = true;
					break;
				}
			}
		}
		Vector3::Spring(mCursorPosition, mCursorVec, mResCursorPos, 0.5f, 0.5, 2.0f);
	}
	else {
		//押す前のボタン点滅
		mButtonAlphaCount += 200.0f*Time::GetInstance().deltaTime();
		mButtonAlpha = Math::Sin(mButtonAlphaCount);
	}

	if ((GamePad::GetInstance().AllTriggerDown() ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) &&
		!mIsPushButton) {
		mIsPushButton = true;
	}
	//α値をクランプ
	mButtonAlpha = Math::Clamp(mButtonAlpha, 0.0f, 1.0f);
	mMenuAlpha = Math::Clamp(mMenuAlpha, 0.0f, 1.0f);

}

void TitleUI::Draw() const
{
	Vector2 titlePos = Vector2(WINDOW_WIDTH / 2.0f, 120.0f);
	Vector2 titleSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::TITLE_SPRITE);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SPRITE, titlePos, titleSize / 2.0f, Vector2(1.3f, 1.3f), true, false);

	Sprite::GetInstance().Draw(SPRITE_ID::BUTTON_START_SPRITE,Vector2(WINDOW_WIDTH/2.0f,450.0f) , mButtonStartSize / 2.0f, mButtonAlpha, Vector2(1.5f,1.5f), true, false);

	for (const auto& i : mStates) {
		Sprite::GetInstance().Draw(i.id, i.position, i.textureSize / 2.0f,mMenuAlpha, Vector2::One , true, false);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_CUROSR_SPRITE, Vector2(mCursorPosition.x,mCursorPosition.y),mCursorSize/2.0f, mMenuAlpha,Vector2::One,true,false);
}

std::vector<TitleUI::CursorState> TitleUI::GetCursorStates()
{
	return mStates;
}
