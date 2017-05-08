#pragma once
#include "../../Actor.h"
#include "../../ID.h"
#include <memory>
#include "../../../GameManager/GameManager.h"
#include <vector>
class GameMasterUI;
class SelectBackUI;
class GameMaster :public Actor
{
public:
	GameMaster(IWorld& world,GameManager& manager);
	~GameMaster();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	//�}�X�^�[�̋C���ς񂾂�
	bool GetMasterIsEnd();
private:
	void PadSetUp();
	void AddPlayer(int size);
private:
	//�X�N���[�����W(Z���W�͉��s��)
	Vector3 mScreenPos;
	//�ʒu
	Vector3 mPosition;
	//�}�X�^�[�e�L�X�g
	GameMasterUI* mMasterText;
	//���E���h��
	int mRaund;
	//�A�j���[�V����

	//�p�b�h���̓t���O
	bool mPlayer2Flag;
	bool mPlayer3Flag;
	bool mPlayer4Flag;
	//���b�Z�[�W�𗬂����Ƃ��ł��邩�ǂ���
	bool mTextSkipFlag;
	//�\�����Ă��郁�b�Z�[�W
	int mTextNum;
	//�Q�[���}�X�^�[�̂��ׂ����Ƃ����ׂďI��������ǂ���
	bool mMasterIsEnd;
	//�p�b�h���
	std::vector<int>mPads;
	//�Q�[���}�l�[�W���[
	GameManager* mManager;
	//���E���h�Ƃ���UI
	SelectBackUI* mBackUi;
};