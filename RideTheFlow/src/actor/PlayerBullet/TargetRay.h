#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"
#include "../Player.h"
#include "../CameraActor.h"
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
	Line GetLine()
	{
		//Line�𐶐�
		Line line;
		Player* player = dynamic_cast<Player*>(world.GetPlayer(parameter.playNumber).get());
		line.startPos = Vector3(player->GetPlayerGunPos());
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		line.endPos = camera->GetTarget();
		return line;
	}
	Line GetSniperLine()
	{
		Player* player = dynamic_cast<Player*>(world.GetPlayer(parameter.playNumber).get());
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		//�e�̈ʒu����X�i�C�p�[�^�[�Q�b�g�̈ʒu�̃x�N�g�����v�Z
		Vector3 vec = (camera->GetTarget() - player->GetPlayerGunPos()).Normalized();
		Line playerGun;
		playerGun.startPos = player->GetPlayerGunPos();
		//�ǂ̂��炢Line���L�т邩��Manager�̃`���[�W�J�E���g���g���Čv�Z
		playerGun.endPos = player->GetPlayerGunPos() + vec*mManager->GetChargeCount().chargeSniperCount;
		return playerGun;
	}
public:
	PlayerAttackState GetState()
	{
		return attackState;
	}
	bool colFlag()
	{
		return mManager->GetChargeCount().isColSniperLine;
	}
	//���킲�Ƃ̃^�[�Q�b�g�̓���
private:
	void MachineGun();
	void SniperGun();

private:
	PlayerAttackManager* mManager;
	CameraActor* mCamera;
	Player* mPlayer;
	//���������ꏊ�̃|�W�V����
	Vector3 mColPos;
	bool isCol;
	//�X�i�C�p�[�̓������Ă���ꏊ
	Vector3 mColSniperPos;
	bool isSniperCol;
	//�v���C���[���������Ă��镐����擾
	PlayerAttackState attackState;
};