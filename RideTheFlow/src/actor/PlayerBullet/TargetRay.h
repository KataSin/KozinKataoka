#pragma once
#include "../Actor.h"
#include <memory>
#include <vector>
#include "../ID.h"
#include "../Player/Player.h"
#include "../../actor/CameraActor/CameraActor.h"
#include "../../actor/Collision.h"
#include "../../world/IWorld.h"
#include "../PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
class TargetRay :public Actor, public std::enable_shared_from_this<TargetRay>
{
public:
	TargetRay(IWorld& world,Actor& manager);
	~TargetRay();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	Line GetLine();
	Line GetSniperLine();
public:
	PlayerAttackState GetState();
	bool colFlag();
	//�������Ă��邩
	bool GetPlayerSniperLineCol();
	//���킲�Ƃ̃^�[�Q�b�g�̓���
private:
	void MachineGun();
	void SniperGun();

private:

	PlayerAttackManager* mManager;
	CameraActor* mCamera;
	Player* mPlayer;
	//���������ꏊ�̃|�W�V��������
	std::vector<Vector3> mColVectorPos;
	Vector3 mColPos;
	bool mIsCol;
	//�X�i�C�p�[�̓������Ă���ꏊ
	Vector3 mColSniperPos;
	bool mIsSniperCol;
	//�v���C���[���������Ă��镐����擾
	PlayerAttackState mAttackState;
	//�v���C���[�ɓ����������ǂ���
	bool mIsPlayerCol;
};