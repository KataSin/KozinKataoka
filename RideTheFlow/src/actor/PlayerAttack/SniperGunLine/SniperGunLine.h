#pragma once
#include "../../Actor.h"
#include "../../Collision.h"
#include "../PlayerAttackManager/PlayerAttackManager.h"
#include "../../Player.h"
#include "../../CameraActor.h"
#include <memory>
class SniperGunLine :public Actor, public std::enable_shared_from_this<SniperGunLine>
{
public:
	SniperGunLine(IWorld& world,Actor& manager);
	~SniperGunLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	//Line GetLine()
	//{
	//	Line playerGun;
	//	playerGun.startPos = mPlayer->GetPlayerGunPos();
	//	playerGun.endPos = endPos;
	//}

	//bool GetCol()
	//{
	//	return mManager->GetChargeCount().isColSniperLine;
	//}
private:
	//���������ꏊ�̃|�W�V����
	Vector3 mColPos;
	//���������t���O
	bool isCol;
	//���̏I�_�̃|�W�V����
	Vector3 endPos;
	//����}�l�[�W���[
	PlayerAttackManager* mManager;
	//�v���C���[
	Player* mPlayer;
	//�J����
	CameraActor* mCamera;
};