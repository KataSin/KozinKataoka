#include "StageSelectUI.h"
#include  "../../input/Keyboard.h"
#include "../../input/GamePad.h"
#include "../../math/Math.h"
#include "../../graphic/Sprite.h"
#include "../../Def.h"
#include "../NumberTexture/NumberTexture.h"
#include "../../actor/SelectSceneActor/SelectScenePlayer.h"
#include "../../world/IWorld.h"
#include "../../sound/Sound.h"
StageSelectUI::StageSelectUI(IWorld & world) :
	UIActor(world),
	mSelectState(SelectState::PLAYER_NUM),
	mIsBackFlag(false),
	mIsNextFlag(false)
{
	parameter.isDead = false;
	mStates.clear();
	//サイズ取得
	mButtonSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::GO_SPRITE) / 2.0f;
	mCursorSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::SELECT_CURSOR_SPRITE) / 2.0f;
	CursorState stateCursor;
	//戻る
	stateCursor.position = Vector2(150, 100);
	stateCursor.state = SelectState::BACK;
	stateCursor.num = 0;
	mStates.push_back(stateCursor);
	//人数
	stateCursor.position = Vector2(750, 200);
	stateCursor.state = SelectState::PLAYER_NUM;
	stateCursor.num = 2;
	mStates.push_back(stateCursor);
	//ラウンド
	stateCursor.position = Vector2(750, 350);
	stateCursor.state = SelectState::RAUND;
	stateCursor.num = 3;
	mStates.push_back(stateCursor);
	//次へ
	stateCursor.position = Vector2(WINDOW_WIDTH - 150, WINDOW_HEIGHT - 100);
	stateCursor.state = SelectState::NEXT;
	stateCursor.num = 0;
	mStates.push_back(stateCursor);


	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3::Zero, MODEL_ID::PLAYER1_MODEL));
	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(15, 0, 30), MODEL_ID::PLAYER2_MODEL));
	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(30, 0, -15), MODEL_ID::PLAYER3_MODEL));
	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(-30, 0, 30), MODEL_ID::PLAYER4_MODEL));

	//走るプレイヤーを追加
	ActorPtr player = std::make_shared<SelectScenePlayer>(world, Vector3::Zero, MODEL_ID::PLAYER1_MODEL);
	mPlayers.push_back(player);
	world.Add(ACTOR_ID::PLAYER_ACTOR, player);

	player = std::make_shared<SelectScenePlayer>(world, Vector3(15, 0, 30), MODEL_ID::PLAYER2_MODEL);
	mPlayers.push_back(player);
	world.Add(ACTOR_ID::PLAYER_ACTOR, player);

	player = std::make_shared<SelectScenePlayer>(world, Vector3(30, 0, -15), MODEL_ID::PLAYER3_MODEL);
	mPlayers.push_back(player);
	world.Add(ACTOR_ID::PLAYER_ACTOR, player);

	player = std::make_shared<SelectScenePlayer>(world, Vector3(-30, 0, 30), MODEL_ID::PLAYER4_MODEL);
	mPlayers.push_back(player);
	world.Add(ACTOR_ID::PLAYER_ACTOR, player);

	mCursorVec = Vector3::Zero;
	Vector2 plus;
	plus = Vector2(32, 64);
	mResCursorPos = Vector3((mStates[SelectState::PLAYER_NUM].position + plus).x,
		(mStates[SelectState::PLAYER_NUM].position + plus).y, 0.0f);
	mCursorPosition = mResCursorPos;
}

StageSelectUI::~StageSelectUI()
{
}

void StageSelectUI::Update(PLAYER_NUMBER playerNumber)
{
	//カーソル移動
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN)||
		GamePad::GetInstance().POVTriggerDown() == 180) {
		mSelectState = (SelectState)((int)mSelectState + 1);
		Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE, DX_PLAYTYPE_BACK);
	}
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP)||
		GamePad::GetInstance().POVTriggerDown() == 0) {
		mSelectState = (SelectState)((int)mSelectState - 1);
		Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE, DX_PLAYTYPE_BACK);
	}
	mSelectState = (SelectState)Math::Clamp((int)mSelectState, 0, mStates.size() - 1);
	//カーソルがどこに行くか
	for (auto& i : mStates) {
		if (i.state == mSelectState) {
			Vector2 plus = Vector2::Zero;
			if (mSelectState == SelectState::PLAYER_NUM ||
				mSelectState == SelectState::RAUND)
				plus = Vector2(32, 64);
			mResCursorPos = Vector3((i.position + plus).x, (i.position + plus).y, 0.0f);
			//バックと次は数字指定いらない
			if ((i.state == SelectState::NEXT || i.state == SelectState::BACK) &&
				(Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)||
				GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))) {
				Sound::GetInstance().PlaySE(SE_ID::CURSOR_YES_SE, DX_PLAYTYPE_BACK);
				i.flag = true;
				break;
			}
			//数設定
			if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT) ||
				GamePad::GetInstance().POVTriggerDown()==270) {
				i.num--;
				Sound::GetInstance().PlaySE(SE_ID::CURSOR_CHANGE_NUM_SE, DX_PLAYTYPE_BACK);
			}
				
			else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT) ||
				GamePad::GetInstance().POVTriggerDown() == 90) {
				i.num++;
				Sound::GetInstance().PlaySE(SE_ID::CURSOR_CHANGE_NUM_SE, DX_PLAYTYPE_BACK);
			}
			//数字のクランプ
			if (i.state == SelectState::PLAYER_NUM)
				i.num = Math::Clamp(i.num, 2, 4);
			else
				i.num = Math::Clamp(i.num, 1, 99);
		}
	}
	//プレイヤーの動き処理
	for (int i = 0; i <= mPlayers.size() - 1; i++) {
		static_cast<SelectScenePlayer*>(mPlayers[i].get())->SetBackFlag(true);
		if (mStates[SelectState::PLAYER_NUM].num > i)
			static_cast<SelectScenePlayer*>(mPlayers[i].get())->SetBackFlag(false);
	}


	Vector3::Spring(mCursorPosition, mCursorVec, mResCursorPos, 0.5f, 0.5, 2.0f);
}

void StageSelectUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK_SPRITE,
		Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
		Sprite::GetInstance().GetSizeVector(SPRITE_ID::SELECT_BACK_SPRITE) / 2,
		Vector2(0.7f, 0.7f), 0.0f);


	Sprite::GetInstance().Draw(SPRITE_ID::GO_SPRITE, mStates[SelectState::NEXT].position, Vector4(255, 255, 255, 1), mButtonSize, 1.0f, 0.5f, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_SPRITE, mStates[SelectState::BACK].position, Vector4(255, 255, 255, 1), mButtonSize, 1.0f, 0.5f, 0.0f);

	SPRITE_ID id = SPRITE_ID::SELECT_CURSOR_SPRITE;
	if (mSelectState == SelectState::PLAYER_NUM ||
		mSelectState == SelectState::RAUND)
		id = SPRITE_ID::SLECT_CURSOR_NUM_SPRITE;

	//カーソルの補間
	Sprite::GetInstance().Draw(id, Vector2(mCursorPosition.x, mCursorPosition.y), Vector4(255, 255, 255, 1), Vector2(mCursorSize.x, mCursorSize.y), 1.0f, Vector2::One, 0.0f);

	//数字設定
	NumberTexture playerNum(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	CursorState numState = mStates[SelectState::PLAYER_NUM];
	playerNum.draw(numState.position, numState.num, Vector4(0, 0, 0, 1), 1.5f);

	NumberTexture raundNum(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	CursorState raundState = mStates[SelectState::RAUND];
	playerNum.draw(raundState.position, raundState.num, Vector4(0, 0, 0, 1), 1.5f);

}

std::vector<StageSelectUI::CursorState> StageSelectUI::GetCursorStates()
{
	return mStates;
}
