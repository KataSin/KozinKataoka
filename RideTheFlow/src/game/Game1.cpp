#include "Game1.h"
#include "../AllInclude.h"
#include "../scene/SceneManager.h"
#include "../scene/TitleScene.h"
#include "../scene/GamePlay.h"
#include "../scene/Result.h"
#include "../scene/SelectScene.h"
#include "../scene/Help.h"
#include "../Def.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include <thread>

Game1::Game1() :
	effectTime(0.0f),
	mPixelShader(-1),
	mRenderTarget(-1),
	mIsLoaded(false),
	mGameManager(std::make_shared<GameManager>())
{

}

void Game1::Initialize()
{
	mIsLoaded = false;

	SetWindowIconID(1);
	Model::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
	Sound::GetInstance().Initialize();


	// ファイルの読み込み
	mContent.LoadSprite(Sprite::GetInstance(), Model::GetInstance());
	mContent.LoadSound(Sound::GetInstance());
	mContent.LoadModel(Model::GetInstance(), false);


	mSceneManager.Add(Scene::Title, std::make_shared<TitleScene>());
	mSceneManager.Add(Scene::GamePlay, std::make_shared<GamePlay>(*mGameManager.get()));
	mSceneManager.Add(Scene::Result, std::make_shared<Result>(*mGameManager.get()));
	mSceneManager.Add(Scene::Select, std::make_shared<SelectScene>(*mGameManager.get()));
	mSceneManager.Add(Scene::Help, std::make_shared<Help>());

	mSceneManager.SetScene(Scene::Title);

	//UIセット
	mSceneManager.SetChangeUi();
}

void Game1::Update()
{
	// 時間を更新
	Time::GetInstance().update();

	// 入力の更新
	Keyboard::GetInstance().Update();
	GamePad::GetInstance().Update();
	// Escキー入力で強制終了
	if (Keyboard::GetInstance().KeyTriggerDown(KEY_INPUT_ESCAPE)||
		mSceneManager.GetEndFlag())
	{
		GameFrame::GameEnd();
		return;
	}

	// シーンが変更されているかを確認
	mSceneManager.Change();
	// シーンを更新
	mSceneManager.Update();
}

void Game1::Draw()
{
	// シーンを描画
	mSceneManager.Draw();
}

void Game1::Finalize()
{
  	mSceneManager.End();
	DeleteGraph(mRenderTarget);
}