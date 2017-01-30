#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GamePlayManager/GamePlayManager.h"
#include "../GameManager/GameManager.h"

class GameTimerUI;
class GamePlayFontUI;
class  GamePlay : public IScene
{

public:
	//�R���X�g���N�^ 
	GamePlay(GameManager& gameManager);
	//�f�X�g���N�^
	~GamePlay();

	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update()override;
	//�`�揈��
	virtual void Draw() override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;

private:
	//�Q�[���v���C�}�l�[�W���[�|�C���^�[
	typedef std::shared_ptr<GamePlayManager>GamePlayManagerPtr;
	GamePlayManagerPtr mGamePlayManager;
	//�Q�[���}�l�[�W���[
	GameManager* mGameManager;
	//���̃V�[��
	Scene mNextScene;
	//�G���h�t���O
	bool  mIsEnd;
	//���[���h
	World wo;
	//���C�g�i���Ԃ�����j
	Light light;
	//�Q�[���^�C�}�[
	GameTimerUI* mGameTimer;
	//�t�H���g
	GamePlayFontUI* fontUi;
	//�������E���h�ڂ�
	int mRandCount;
	//�����E���h�ڂɏI��邩
	int mEndRaundCount;
	//�X�^�[�g���̃t�H���g�t���O
	bool mStartFontFlag;
	//�t�H���g�t���O
	bool mFontFlag;
	bool mIsEndRanund;
	//�������v���C���[
	PLAYER_NUMBER mWinPlayer;
};