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


	// �t�@�C���̓ǂݍ���
	mContent.LoadSprite(Sprite::GetInstance(), Model::GetInstance());
	mContent.LoadSound(Sound::GetInstance());
	mContent.LoadModel(Model::GetInstance(), false);


	mSceneManager.Add(Scene::Title, std::make_shared<TitleScene>());
	mSceneManager.Add(Scene::GamePlay, std::make_shared<GamePlay>(*mGameManager.get()));
	mSceneManager.Add(Scene::Result, std::make_shared<Result>(*mGameManager.get()));
	mSceneManager.Add(Scene::Select, std::make_shared<SelectScene>(*mGameManager.get()));
	mSceneManager.Add(Scene::Help, std::make_shared<Help>());

	mSceneManager.SetScene(Scene::Title);

	//UI�Z�b�g
	mSceneManager.SetChangeUi();
}

void Game1::Update()
{
	// ���Ԃ��X�V
	Time::GetInstance().update();

	// ���͂̍X�V
	Keyboard::GetInstance().Update();
	GamePad::GetInstance().Update();
	// Esc�L�[���͂ŋ����I��
	if (Keyboard::GetInstance().KeyTriggerDown(KEY_INPUT_ESCAPE)||
		mSceneManager.GetEndFlag())
	{
		GameFrame::GameEnd();
		return;
	}

	// �V�[�����ύX����Ă��邩���m�F
	mSceneManager.Change();
	// �V�[�����X�V
	mSceneManager.Update();
}

void Game1::Draw()
{
	// �V�[����`��
	mSceneManager.Draw();
}

void Game1::Finalize()
{
  	mSceneManager.End();
	DeleteGraph(mRenderTarget);
}