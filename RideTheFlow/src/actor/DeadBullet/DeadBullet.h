#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class DeadBullet :public Actor, public std::enable_shared_from_this<DeadBullet>
{
public:
	DeadBullet(IWorld& world, Vector3 position, PLAYER_NUMBER player);
	~DeadBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//�ʒu
	Vector3 mPosition;
	//�����x
	Vector3 mInitialVelocity;
	//�x�N�g��
	Vector3 vec;
	//����
	Vector3 mFrontVec;
	//�ʒu
	//1�t���[���O�̃|�W�V����
	Vector3 coppyPos;
	Vector3 vecPos;
};