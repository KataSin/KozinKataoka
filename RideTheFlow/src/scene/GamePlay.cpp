#include "GamePlay.h"
#include "../AllInclude.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"

#include "../math/Math.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../game/Random.h"

#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include "../actor/ParticleManager/ParticleManager.h"
#include "../actor/ID.h"
#include "../actor/StageLineManager/StageLine/StageLine.h"
#include "../actor/Pool/Pool.h"
#include "../UIactor/GameTimer/GameTimerUI.h"
#include "../UIactor/GameFrameUI/GameFrameUI.h"
//�R���X�g���N�^
GamePlay::GamePlay(GameManager& gameManager) :
	mGameManager(&gameManager),
	mRandCount(0)
{

}

//�f�X�g���N�^
GamePlay::~GamePlay()
{

}

//�J�n
void GamePlay::Initialize()
{
	mIsEnd = false;
	mNextScene = Scene::GamePlay;
	//���E���h��ݒ�
	mEndRaundCount = 3;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	wo.UIAdd(UI_ID::GAMETIMER_UI, std::make_shared<GameTimerUI>(wo, Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 20.0f));
	wo.UIAdd(UI_ID::GAMEFRAME_UI, std::make_shared<GameFrameUI>(wo, Vector2::Zero));

	mGamePlayManager = std::make_shared<GamePlayManager>(wo);

	SetLightEnable(true);
	SetLightDirection(Vector3::ToVECTOR(Vector3(-1, -1, -1)));

	//���C�g�̐ݒ�(�s�����)
	//light.SetDirectionalLight("GamePlayLight", Vector3(-1, -1, -1));
}

void GamePlay::Update()
{
	wo.Update();
	if (mGamePlayManager->EndRaund()) {
		mIsEnd = true;
		mGamePlayManager->IsWinPlayer();
		mRandCount++;
		//�S���E���h�I����Ă��烊�U���g��
		if (mRandCount>mEndRaundCount) {
			mNextScene = Scene::Result;
			//�������l�������Z�b�g
			mGameManager->SetPlayerRank(mGamePlayManager->IsFinalWinPlayer());
		}
	}
}

//�`��
void GamePlay::Draw()
{
	//�J�����̕`�ʂ̈ʒu��ݒ�
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera();
	//�J�����̕`�ʈʒu��ݒ肵�I�������Ƀv���C���[���Ƃ�UI��Update����Draw�����Ȃ��Ă͂����Ȃ�
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_4).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_4);
	wo.Draw();
	//UI�\���̂��ߐݒ��������
	SetCameraScreenCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//UI�͈�񂾂�draw��OK
	wo.UIDraw();
	DrawFormatString(0, 368, GetColor(255, 255, 255), "�Q�[���v���C�V�[��");
	//DrawSphere3D(Vector3::ToVECTOR(Vector3(0,0,0)), 1.0f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

//�I�����Ă��邩�H
bool GamePlay::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene GamePlay::Next() const
{
	return mNextScene;
}

void GamePlay::End()
{
	mRandCount++;
	//���U���g��������0�ɂ���
	if (mNextScene == Scene::Result)
		mRandCount = 0;
	wo.Clear();
}