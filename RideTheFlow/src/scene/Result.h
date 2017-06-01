#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../GameManager/GameManager.h"
#include <vector>

class  Result : public IScene
{

public:
	//�R���X�g���N�^ 
	Result(GameManager& gameManager);
	//�f�X�g���N�^
	~Result();

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
	GameManager* mGameManager;
	bool  mIsEnd;
	World wo;
	//�X�e�[�W�̃}�g���b�N�X
	Matrix4 mStageMat;
	//��̃}�g���b�N�X
	Matrix4 mDaiMat;
	//�X�J�C�{�b�N�X�}�g���b�N�X
	Matrix4 mSkyMat;
	//���ʂɉ����Ă̍��W
	std::vector<Vector3> mRankPos;

	//�J�����̈ʒu
	Vector3 mCameraPos;
	//�J�����̍s���ׂ��ʒu
	Vector3 mResCameraPos;
	//�J�������x
	Vector3 mCameraVelo;


	//�A�N�V�����^�C��(�C�x���g�n)
	float mActionTime;

	//UI��
	int test;
};