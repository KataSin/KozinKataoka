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
	//当たった場所のポジション
	Vector3 mColPos;
	//当たったフラグ
	bool isCol;
	//線の終点のポジション
	Vector3 endPos;
	//武器マネージャー
	PlayerAttackManager* mManager;
	//プレイヤー
	Player* mPlayer;
	//カメラ
	CameraActor* mCamera;
};