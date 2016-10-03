#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"
#include "../Player.h"
#include "../CameraActor.h"
#include "../../actor/Collision.h"

class SniperBullet :public Actor, public std::enable_shared_from_this<SniperBullet>
{
public:
	SniperBullet(IWorld& world, Player& player);
	~SniperBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	Line GetLine()
	{
		//Lineを生成
		Line line;
		line.startPos = Vector3(mPlayer->GetPlayerGunPos());
		line.endPos = Vector3();
		return line;
	}

private:
	Player* mPlayer;
	CameraActor* mCameraActor;
	//当たった場所のポジション
	Vector3 mColPos;
	bool isCol;
	//プレイヤーが今持っている武器を取得
	PlayerAttackState attackState;
};