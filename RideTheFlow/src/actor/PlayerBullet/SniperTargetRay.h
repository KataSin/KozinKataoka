#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"
#include "../Player.h"
#include "../CameraActor.h"
#include "../../actor/Collision.h"

class SniperTargetRay :public Actor, public std::enable_shared_from_this<SniperTargetRay>
{
public:
	SniperTargetRay(IWorld& world, Player& player);
	~SniperTargetRay();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	Line GetLine()
	{
		//Line�𐶐�
		Line line;
		line.startPos = Vector3(mPlayer->GetPlayerGunPos());
		line.endPos = Vector3(mPlayer->GetBulletTarget());
		return line;
	}

private:
	Player* mPlayer;
	//���������ꏊ�̃|�W�V����
	Vector3 mColPos;
	bool isCol;
	//�v���C���[���������Ă��镐����擾
	PlayerAttackState attackState;
};