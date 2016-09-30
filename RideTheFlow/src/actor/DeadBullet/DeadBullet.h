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
	//位置
	Vector3 mPosition;
	//初速度
	Vector3 mInitialVelocity;
	//ベクトル
	Vector3 vec;
	//方向
	Vector3 mFrontVec;
	//位置
	//1フレーム前のポジション
	Vector3 coppyPos;
	Vector3 vecPos;
};