#include "SelectScene.h"
#include "../input/Keyboard.h"
#include "../actor/SelectSceneActor/RunStage.h"
#include "../input/GamePad.h"
#include "../actor/SelectSceneActor/GameMaster/GameMaster.h"
#include "../UIactor/StageSelectUI/StageSelectUI.h"
#include "../actor/SelectSceneActor/SelectSceneCamera.h"
#include "../actor/SelectSceneActor/SelectScenePlayer.h"
SelectScene::SelectScene(GameManager & gameManager) :
	mGameManager(&gameManager)
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	//初期化
	mIsEnd = false;
	mSelectUi = std::make_shared<StageSelectUI>(wo);
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<RunStage>(wo));
	//没です
	//wo.Add(ACTOR_ID::MANAGER_ACTOR, mMaster);
	mScene = Scene::Title;
	wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SelectSceneCamera>(wo, Vector3(60, 40, 130), Vector3(0, 10)));
	wo.UIAdd(UI_ID::SELECT_UI, mSelectUi);
	mPads.clear();
	//パッド設定(前仕様の名残)
	mPads.push_back(DX_INPUT_PAD1);
	mPads.push_back(DX_INPUT_PAD2);
	mPads.push_back(DX_INPUT_PAD3);
	mPads.push_back(DX_INPUT_PAD4);

}

void SelectScene::Update()
{
	//if (dynamic_cast<GameMaster*>(mMaster.get())->GetMasterIsEnd()) {
	//	mIsEnd = true;
	//}
	auto state = static_cast<StageSelectUI*>(mSelectUi.get())->GetCursorStates();
	//次へのボタン押されたら
	if (state[StageSelectUI::SelectState::NEXT].flag) {
		mScene = Scene::GamePlay;
		//各種設定
		mGameManager->SetPlayerNum(state[StageSelectUI::SelectState::PLAYER_NUM].num);
		mGameManager->SetRaundCount(state[StageSelectUI::SelectState::RAUND].num);
		mGameManager->SetPlayerPad(mPads);
		mIsEnd = true;
	}
	//戻るを押されたら
	if (state[StageSelectUI::SelectState::BACK].flag) {
		mIsEnd = true;
		mScene = Scene::Title;
	}

	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
}

void SelectScene::Draw()
{
	wo.Draw();
	wo.UIDraw();
}

bool SelectScene::IsEnd() const
{
	return mIsEnd;
}

Scene SelectScene::Next() const
{
	return mScene;
}

void SelectScene::End()
{
	wo.Clear();
}
