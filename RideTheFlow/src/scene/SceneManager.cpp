#define NOMINMAX
#include"SceneManager.h"
#include"IScene.h"
#include <algorithm>
#include "../time/Time.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../UIactor/SceneChangeManager/SceneChangeManager.h"
const int SceneManager::MaxStageCount = 2;

//�R���X�g���N�^
SceneManager::SceneManager() :
	mStageCount(1),
	mIsGameEnd(false)
{
}

//�X�V�O������
void SceneManager::Initialize() {
	End();
	mScenes.clear();
	//wo.Clear();
}

//�X�V
void SceneManager::Update() {
	mCurrentScene->Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

}

//�`��
void SceneManager::Draw() {
	mCurrentScene->Draw();
	wo.UIDraw();
}

//�I��
void SceneManager::End() {
	mCurrentScene->End();
}

void SceneManager::Change()
{
	//�V�[���`�F���W���͕ύX�ł��Ȃ�
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

//�V�[���̒ǉ�
void SceneManager::Add(Scene name, const IScenePtr& scene) {
	mScenes[name] = scene;
}

void SceneManager::SetScene(Scene name) {
	mCurrentScene = mScenes[name];
	mCurrentScene->Initialize();
}

//�V�[���̕ύX
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

// ���������w�肷��
void SceneManager::Init(Scene name)
{
	mScenes.at(name)->Initialize();
}

// �I���������w�肷��
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
