#include "SelectScene.h"
#include "../input/Keyboard.h"
#include "../actor/SelectSceneActor/RunStage.h"
#include "../input/GamePad.h"
#include "../actor/SelectSceneActor/GameMaster/GameMaster.h"

SelectScene::SelectScene(GameManager & gameManager) :
	mGameManager(&gameManager)
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	//èâä˙âª
	mIsEnd = false;
	mMaster = std::make_shared<GameMaster>(wo, *mGameManager);
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<RunStage>(wo));
	wo.Add(ACTOR_ID::MANAGER_ACTOR, mMaster);
}

void SelectScene::Update()
{
	if (dynamic_cast<GameMaster*>(mMaster.get())->GetMasterIsEnd()) {
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
