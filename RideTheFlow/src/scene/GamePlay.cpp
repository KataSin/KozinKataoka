#include "GamePlay.h"
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
#include "../UIactor/ResultUI/ResultUI.h"
#include "../UIactor/GamePlayFontUI/GamePlayFontUI.h"
//�R���X�g���N�^
GamePlay::GamePlay(GameManager& gameManager) :
	mGameManager(&gameManager),
	mRandCount(0),
	mPlayerNum(0)
{
	mGamePlayManager = std::make_shared<GamePlayManager>(wo);
}

//�f�X�g���N�^
GamePlay::~GamePlay()
{

}

//�J�n
void GamePlay::Initialize()
{
	//�t���O������
	mIsEnd = false;
	mIsEndRanund = false;
	mStartFontFlag = true;
	mFontFlag = true;
	//�v���C�l���ݒ�
	mPlayerNum = mGameManager->GetPlayerNum();
	wo.SetPlayerNum(mPlayerNum);
	//�p�b�h�������[���h�ɐݒ�
	wo.SetPadNum(mGameManager->GetPlayerPad());
	//�����Q�[���v���C�Ɉڍs
	mNextScene = Scene::GamePlay;
	//���E���h��ݒ�
	mEndRaundCount = mGameManager->GetRaundCount();
	//�X�e�[�W��ǉ�
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	//�^�C�}�[�ݒ�
	auto gameTimer = std::make_shared<GameTimerUI>(wo, Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 180.0f);
	//�^�C�}�[��ǉ�
	wo.UIAdd(UI_ID::GAMETIMER_UI, gameTimer);
	mGameTimer = gameTimer.get();
	//�Q�[���t���[����ǉ�
	wo.UIAdd(UI_ID::GAMEFRAME_UI, std::make_shared<GameFrameUI>(wo, Vector2::Zero, mPlayerNum));
	auto font = std::make_shared<GamePlayFontUI>(wo);
	//�t�H���g�}�l�[�W���[��ǉ�
	wo.UIAdd(UI_ID::FONT_UI, font);
	fontUi = static_cast<GamePlayFontUI*>(font.get());
	//�ŏ��ɏo���t�H���g��ݒ�
	fontUi->StartFont(SPRITE_ID::YO_I_FONT_SPRITE);

	//SetLightEnable(true);
	//SetLightDirection(Vector3::ToVECTOR(Vector3(-1, -1, -1)));

	//�������v���C���[������
	mWinPlayer = PLAYER_NUMBER::PLAYER_NULL;
	//�v���C���[����s�\
	wo.SetInputPlayer(false);
	//�x���̓^�C�}�[�������Ă��Ȃ�
	gameTimer->StopTimer(true);

	mSeTimer = 0.0f;
	mSeFlag = true;

	mRaundTimeUpFlag = false;
	mRaundNoPlayerFlag = false;
}

void GamePlay::Update()
{
	mSeTimer += Time::GetInstance().deltaTime();
	if (mSeTimer >= 0.8f&&mSeFlag) {
		Sound::GetInstance().PlaySE(SE_ID::GAME_PLAY_START_SE, DX_PLAYTYPE_BACK);
		mSeFlag = false;
	}
	//��[���t�H���g���I�������v���C���[�̑���J�n
	if (fontUi->GetEndFont(SPRITE_ID::YO_I_FONT_SPRITE) && mStartFontFlag) {
		fontUi->StartFont(SPRITE_ID::DON_SPRITE, 8.0f);
		wo.SetInputPlayer(true);
		mGameTimer->StopTimer(false);
		mStartFontFlag = false;
		int rand = std::rand() % 2;
		if (rand == 1)
			mBgm = BGM_ID::GAME_PLAY_1_BGM;
		else
			mBgm = BGM_ID::GAME_PLAY_2_BGM;
		Sound::GetInstance().PlayBGM(mBgm, DX_PLAYTYPE_LOOP);

	}

	if (mIsEndRanund) {
		if ((GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) ||
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))&&
			!mIsEnd) {
			mIsEnd = true;
			mRandCount++;
			Sound::GetInstance().PlaySE(SE_ID::CURSOR_YES_SE, DX_PLAYTYPE_BACK);
			//�S���E���h�I����Ă��烊�U���g��
			if (mRandCount >= mEndRaundCount) {
				mNextScene = Scene::Result;
				//�������l�������Z�b�g
				mGameManager->SetPlayerRank(mGamePlayManager->IsFinalWinPlayer());
			}
		}
	}
	else
	{
		if (mGamePlayManager->EndRaund() && !mRaundTimeUpFlag) {
			if (mFontFlag) {
				Sound::GetInstance().StopBGM();
				Sound::GetInstance(). PlaySE(SE_ID::GAME_PLAY_END_SE,DX_PLAYTYPE_BACK);
				mGameTimer->StopTimer(true);
				//�������v���C���[������
				mWinPlayer = mGamePlayManager->IsWinPlayer();
				//�����܂ŕ\��
				fontUi->StartFont(SPRITE_ID::SOKOMADE_FONT_SPRITE);
				mFontFlag = false;
				mRaundNoPlayerFlag = true;
			}
			else if (fontUi->GetEndFont(SPRITE_ID::SOKOMADE_FONT_SPRITE)) {
				//�����܂ŕ\���I������烊�U���g�摜��\��
				Sound::GetInstance().PlayBGM(BGM_ID::GAME_PLAY_END_BGM);
				wo.UIAdd(UI_ID::RESULT_UI, std::make_shared<ResultUI>(wo, *mGamePlayManager.get(), mWinPlayer));
				mIsEndRanund = true;
				mFontFlag = true;
			}
		}
		else if (mGamePlayManager->TimeUp()&&!mRaundNoPlayerFlag) {
			if (mFontFlag) {
				Sound::GetInstance().StopBGM();
				Sound::GetInstance().PlaySE(SE_ID::GAME_PLAY_END_SE, DX_PLAYTYPE_BACK);
				mGameTimer->StopTimer(true);
				//�����܂ŕ\��
				fontUi->StartFont(SPRITE_ID::SOKOMADE_FONT_SPRITE);
				mFontFlag = false;
				mRaundTimeUpFlag = true;
			}
			else if (fontUi->GetEndFont(SPRITE_ID::SOKOMADE_FONT_SPRITE)) {
				//���������\��(������)
				Sound::GetInstance().PlayBGM(BGM_ID::GAME_PLAY_END_BGM);
				fontUi->StartFont(SPRITE_ID::HIKIWAKE_FONT_SPRITE, true);
				mFontFlag = true;
				mIsEndRanund = true;
			}
		}
	}
	wo.Update();
}

//�`��
void GamePlay::Draw()
{
	//�J���������̐ݒ�
	SetCamera(mPlayerNum);
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
	//���U���g��������0�ɂ��違���������Z�b�g
	if (mNextScene == Scene::Result) {
		mRandCount = 0;
		mGamePlayManager->ResetWin();
	}
	Sound::GetInstance().StopBGM();
	wo.Clear();
}

void GamePlay::SetCamera(int num)
{
	switch (num)
	{
	case 2:
	{
		//�J�����̕`�ʂ̈ʒu��ݒ�
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//�J�����̕`�ʈʒu��ݒ肵�I�������Ƀv���C���[���Ƃ�UI��Update����Draw�����Ȃ��Ă͂����Ȃ�
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		wo.Draw();
		break;
	}
	case 3:
	{
		//�J�����̕`�ʂ̈ʒu��ݒ�
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//�J�����̕`�ʈʒu��ݒ肵�I�������Ƀv���C���[���Ƃ�UI��Update����Draw�����Ȃ��Ă͂����Ȃ�
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
		wo.Draw();
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		break;
	}
	case 4:
	{
		//�J�����̕`�ʂ̈ʒu��ݒ�
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//�J�����̕`�ʈʒu��ݒ肵�I�������Ƀv���C���[���Ƃ�UI��Update����Draw�����Ȃ��Ă͂����Ȃ�
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_4).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_4);
		wo.Draw();
		break;
	}

	}
}
