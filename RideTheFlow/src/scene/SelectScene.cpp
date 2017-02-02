#include "SelectScene.h"
#include "../actor/SelectSceneActor/SelectScenePlayer.h"
#include "../actor/SelectSceneActor/SelectSceneCamera.h"
#include "../UIactor/SelectSceneUI/GameMasterUI/GameMasterUI.h"
#include "../input/Keyboard.h"
#include "../actor/SelectSceneActor/RunStage.h"
SelectScene::SelectScene(GameManager & gameManager):
	mGameManager(&gameManager)
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	mIsEnd = false;
	wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<SelectSceneCamera>(wo, Vector3(60,40,130), Vector3(0,10)));
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(wo, Vector3::Zero, MODEL_ID::PLAYER1_MODEL));
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(wo, Vector3(15,0,30), MODEL_ID::PLAYER2_MODEL));
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(wo, Vector3(30,0,-15), MODEL_ID::PLAYER3_MODEL));
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<SelectScenePlayer>(wo, Vector3(-30,0,30), MODEL_ID::PLAYER4_MODEL));
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<RunStage>(wo));
	wo.UIAdd(UI_ID::TEX_BACK_UI, std::make_shared<GameMasterUI>(wo));

	mGameManager->SetPlayerNum(2);
}

void SelectScene::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
		mIsEnd = true;
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
	return Scene::GamePlay;
}

void SelectScene::End()
{
	wo.Clear();
}
