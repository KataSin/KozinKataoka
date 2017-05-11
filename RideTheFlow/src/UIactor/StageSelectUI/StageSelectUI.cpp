#include "StageSelectUI.h"
#include  "../../input/Keyboard.h"
#include "../../math/Math.h"
#include "../../graphic/Sprite.h"
#include "../../Def.h"
#include "../NumberTexture/NumberTexture.h"
#include "../../actor/SelectSceneActor/SelectScenePlayer.h"
#include "../../world/IWorld.h"
StageSelectUI::StageSelectUI(IWorld & world) :
	UIActor(world),
	mSelectState(SelectState::BACK),
	mIsBackFlag(false),
	mIsNextFlag(false)
{
	parameter.isDead = false;
	mStates.clear();

	CursorState stateCursor;
	//戻る
	stateCursor.position = Vector2(32, 32);
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
	stateCursor.position = Vector2(WINDOW_WIDTH - 128, WINDOW_HEIGHT - 128);
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

}

StageSelectUI::~StageSelectUI()
{
}

void StageSelectUI::Update(PLAYER_NUMBER playerNumber)
{
	//カーソル移動
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
		mSelectState = (SelectState)((int)mSelectState + 1);
	else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
		mSelectState = (SelectState)((int)mSelectState - 1);
	mSelectState = (SelectState)Math::Clamp((int)mSelectState, 0, mStates.size() - 1);

	//カーソルがどこに行くか
	for (auto& i : mStates) {
		if (i.state == mSelectState) {
			mCursorPosition = i.position;
			//バックと次は数字指定いらない
			if ((i.state == SelectState::NEXT || i.state == SelectState::BACK)&&
				Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
				i.flag = true;
				break;
			}
			//数設定
			if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
				i.num--;
			else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
				i.num++;
			//数字のクランプ
			if (i.state == SelectState::PLAYER_NUM)
				i.num = Math::Clamp(i.num, 2, 4);
			else
				i.num = Math::Clamp(i.num, 1, 99);
		}
	}
	//プレイヤーの動き処理
	for (int i = 0; i <= mPlayers.size()-1; i++) {
		static_cast<SelectScenePlayer*>(mPlayers[i].get())->SetBackFlag(true);
		if (mStates[SelectState::PLAYER_NUM].num > i)
			static_cast<SelectScenePlayer*>(mPlayers[i].get())->SetBackFlag(false);
	}
}

void StageSelectUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_BACK_SPRITE,
		Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
		Sprite::GetInstance().GetSizeVector(SPRITE_ID::SELECT_BACK_SPRITE) / 2,
		Vector2(0.7f, 0.7f), 0.0f);

	Sprite::GetInstance().Draw(SPRITE_ID::SELECT_CURSOR_SPRITE, mCursorPosition, 1.0f);

	//数字設定
	NumberTexture playerNum(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	CursorState numState = mStates[SelectState::PLAYER_NUM];
	playerNum.draw(numState.position, numState.num, Vector4(0, 0, 0, 1));

	NumberTexture raundNum(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	CursorState raundState = mStates[SelectState::RAUND];
	playerNum.draw(raundState.position, raundState.num, Vector4(0, 0, 0, 1));

}

std::vector<StageSelectUI::CursorState> StageSelectUI::GetCursorStates()
{
	return mStates;
}
