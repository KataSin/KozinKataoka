#define NOMINMAX
#include"SceneManager.h"
#include"IScene.h"
#include <algorithm>
#include "../time/Time.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../UIactor/SceneChangeManager/SceneChangeManager.h"
const int SceneManager::MaxStageCount = 2;

//コンストラクタ
SceneManager::SceneManager() :
	mStageCount(1),
	mIsGameEnd(false)
{
}

//更新前初期化
void SceneManager::Initialize() {
	End();
	mScenes.clear();
	//wo.Clear();
}

//更新
void SceneManager::Update() {
	mCurrentScene->Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

}

//描画
void SceneManager::Draw() {
	mCurrentScene->Draw();
	wo.UIDraw();
}

//終了
void SceneManager::End() {
	mCurrentScene->End();
}

void SceneManager::Change()
{
	//シーンチェンジ中は変更できない
	if (mCurrentScene->IsEnd()&& static_cast<SceneChangeManager*>(mChangeUi.get())->GetNoBlockFlag())
	{
		ChangeSceneSet(mCurrentScene->Next());
		static_cast<SceneChangeManager*>(mChangeUi.get())->ChangeJudge(true);
	}

	if (static_cast<SceneChangeManager*>(mChangeUi.get())->GetYesBlockFlag())
	{
		Change(mCurrentScene->Next());
		static_cast<SceneChangeManager*>(mChangeUi.get())->ChangeJudge(false);
	}
}

//シーンの追加
void SceneManager::Add(Scene name, const IScenePtr& scene) {
	mScenes[name] = scene;
}

void SceneManager::SetScene(Scene name) {
	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
}

//シーンの変更
void SceneManager::Change(Scene name) {
	Scene now = Scene::None;
	for (auto& i : mScenes)
	{
		if (mCurrentScene == i.second)
			now = i.first;
	}
	End();
	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
}

// 初期化を指定する
void SceneManager::Init(Scene name)
{
	mScenes.at(name)->Initialize();
}

// 終了処理を指定する
void SceneManager::Final(Scene name)
{
	mScenes.at(name)->End();
}

static int _Clamp(int t, int min, int max)
{
	return std::min(max, std::max(t, min));
}

void SceneManager::SetStageCount(int n)
{
	mStageCount = _Clamp(n, 0, SceneManager::MaxStageCount);
}

void SceneManager::SetChangeUi()
{
	UIActorPtr ui = std::make_shared<SceneChangeManager>(wo);
	mChangeUi = ui;
	wo.UIAdd(UI_ID::CHANGE_BLOK_UI, ui);
}

bool SceneManager::GetEndFlag()
{
	return mCurrentScene->GetGameEndFlag();
}

void SceneManager::ChangeSceneSet(Scene scene)
{
	switch (scene)
	{
	case Scene::Title:
		static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_TITLE_SPRITE);
		break;
	case Scene::GamePlay:
	{
		if (mScenes[mCurrentScene->Next()] == mCurrentScene)
			static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_NEXT_RAUND_SPRITE);
		else
			static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_GAME_PLAY_SPRITE);
		break;
	}

	case Scene::Select:
		static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_STAGE_SELECT_SPRITE);
		break;
	case Scene::Result:
		static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_RESULT_SPRITE);
		break;
	case Scene::Help:
		static_cast<SceneChangeManager*>(mChangeUi.get())->SpriteSet(SPRITE_ID::SCENE_CHANGE_HELP_SPRITE);
		break;
	}
}
