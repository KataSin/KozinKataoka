#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"
#include "../Player.h"
#include "../CameraActor.h"
#include "../../actor/Collision.h"
#include "../../world/IWorld.h"

class TargetRay :public Actor, public std::enable_shared_from_this<TargetRay>
{
public:
	TargetRay(IWorld& world,Actor& target);
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
	//���킲�Ƃ̃^�[�Q�b�g�̓���
private:
	void MachineGun();
	void SniperGun();

private:
	Actor* mTarget;
	//���������ꏊ�̃|�W�V����
	Vector3 mColPos;

	bool isCol;
	//�v���C���[���������Ă��镐����擾
	PlayerAttackState attackState;
};