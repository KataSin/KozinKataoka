#include "GameMaster.h"
#include "../../Collision.h"
#include "../SelectSceneCamera.h"
#include "../SelectScenePlayer.h"
#include "../../../world/World.h"
#include "../../../Text/TxetRead/TextRead.h"
#include "../../../UIactor/SelectSceneUI/GameMasterUI/GameMasterUI.h"
#include "../../../UIactor/SelectBackUI/SelectBackUI.h"
#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"
GameMaster::GameMaster(IWorld& world, GameManager& manager) :
	Actor(world),
	mManager(&manager),
	mTextNum(0)
{
	mRaund = 3;
	mPlayer2Flag = false;
	mPlayer3Flag = false;
	mPlayer4Flag = false;
	mMasterIsEnd = false;

	mTextSkipFlag = true;
	//ゲームマスターのテキストを読み込む
	TextRead::GetInstance().ReadTxt(TEXT_FILE_ID::GAMEMASTER_TXT, "res/TextFile/GameMaster.txt", 9);
	auto master = std::make_shared<GameMasterUI>(world);
	auto back = std::make_shared<SelectBackUI>(world);
	mMasterText = master.get();
	mBackUi = back.get();
	world.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SelectSceneCamera>(world, Vector3(60, 40, 130), Vector3(0, 10)));
	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3::Zero, MODEL_ID::PLAYER1_MODEL));
	world.UIAdd(UI_ID::TEX_BACK_UI,master);
	world.UIAdd(UI_ID::SELECT_BACK_UI, back);


	mPads.clear();
	mPads.push_back(PADNUM::PAD1);
	manager.SetPlayerNum(1);

}

GameMaster::~GameMaster()
{
}

void GameMaster::Update()
{
	if (GamePad::GetInstance().AllTriggerDown() || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::I) && mTextSkipFlag) {
		mTextNum++;
		mMasterText->SetMasterText(mTextNum);
	}
	if (mMasterText->GetMasterText() == 1) {
		//パッドセット
		PadSetUp();
		//UIの動き設定
		mBackUi->SetMove(BackUiMove::UIMOVE_START);
		//番号設定
		mBackUi->SetNumber(mPads.size());
		mTextSkipFlag = false;
		//パッド入力終わったかどうか（キー設定変える事）
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::G )) {
			mTextNum++;
			mMasterText->SetMasterText(mTextNum);
			mTextSkipFlag = true;
			mBackUi->SetMove(BackUiMove::UIMOVE_END);
		}
	}
	if (mMasterText->GetMasterText() == 3) {
		mBackUi->SetMove(BackUiMove::UIMOVE_START);
		mBackUi->SetSpriteID(SPRITE_ID::UP_RAUND_SPRITE);
		mBackUi->SetNumber(mRaund);
		mTextSkipFlag = false;
		//パッド入力終わったかどうか（キー設定変える事）
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::G)) {
			mBackUi->SetMove(BackUiMove::UIMOVE_END);
			mTextNum++;
			mMasterText->SetMasterText(mTextNum);
			mTextSkipFlag = true;
		}
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::SPACE)) {
		mManager->SetPlayerPad(mPads);
		mManager->SetPlayerNum(mPads.size());
		mManager->SetRaundCount(mRaund);
		mMasterIsEnd = true;
	}
}

void GameMaster::Draw() const
{
	DrawFormatString(100, 200, GetColor(255, 0, 0), "数:%d", mPads.size());

}

void GameMaster::OnCollide(Actor & other, CollisionParameter colpara)
{
}

bool GameMaster::GetMasterIsEnd()
{
	return mMasterIsEnd;
}

void GameMaster::PadSetUp()
{
	if (!mPlayer2Flag&&GamePad::GetInstance().AnyTriggerDown(PADNUM::PAD2)||Keyboard::GetInstance().KeyTriggerDown(KEYCODE::L)) {
		mPads.push_back(PADNUM::PAD2);
		AddPlayer(mPads.size());
		mPlayer2Flag = true;
	}
	if (!mPlayer3Flag&&GamePad::GetInstance().AnyTriggerDown(PADNUM::PAD3) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::L)) {
		mPads.push_back(PADNUM::PAD3);
		AddPlayer(mPads.size());
		mPlayer3Flag = true;
	}
	if (!mPlayer4Flag&&GamePad::GetInstance().AnyTriggerDown(PADNUM::PAD4)) {
		mPads.push_back(PADNUM::PAD4);
		AddPlayer(mPads.size());
		mPlayer4Flag = true;
	}
}

void GameMaster::AddPlayer(int size)
{
	if (size == 2)	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(15, 0, 30), MODEL_ID::PLAYER2_MODEL));
	if (size == 3)  world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(30, 0, -15), MODEL_ID::PLAYER3_MODEL));
	if (size == 4)	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(world, Vector3(-30, 0, 30), MODEL_ID::PLAYER4_MODEL));
}
