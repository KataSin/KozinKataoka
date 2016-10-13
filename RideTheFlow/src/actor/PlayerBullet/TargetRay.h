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
		//Lineを生成
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
		//銃の位置からスナイパーターゲットの位置のベクトルを計算
		Vector3 vec = (camera->GetTarget() - player->GetPlayerGunPos()).Normalized();
		Line playerGun;
		playerGun.startPos = player->GetPlayerGunPos();
		//どのくらいLineが伸びるかをManagerのチャージカウントを使って計算
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
	//武器ごとのターゲットの動き
private:
	void MachineGun();
	void SniperGun();

private:
	PlayerAttackManager* mManager;
	CameraActor* mCamera;
	Player* mPlayer;
	//当たった場所のポジション
	Vector3 mColPos;
	bool isCol;
	//スナイパーの当たっている場所
	Vector3 mColSniperPos;
	bool isSniperCol;
	//プレイヤーが今持っている武器を取得
	PlayerAttackState attackState;
};