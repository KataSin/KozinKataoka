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
		//Lineを生成
		Line line;
		Player* player = dynamic_cast<Player*>(world.GetPlayer(parameter.playNumber).get());
		line.startPos = Vector3(player->GetPlayerGunPos());
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		line.endPos = camera->GetTarget();
		return line;
	}
	//武器ごとのターゲットの動き
private:
	void MachineGun();
	void SniperGun();

private:
	Actor* mTarget;
	//当たった場所のポジション
	Vector3 mColPos;

	bool isCol;
	//プレイヤーが今持っている武器を取得
	PlayerAttackState attackState;
};