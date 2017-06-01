#pragma once
#include "../UIActor.h"
#include "../../GameManager/GameManager.h"
#include "../../math/Matrix4.h"
#include <vector>
#include <memory>
class EndResultUI : public UIActor
{
public:
	EndResultUI(IWorld& world, GameManager& gameManager);
	~EndResultUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//�Q�[���}�l�[�W���[
	GameManager* mGameManager;
	bool  mIsEnd;
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

};