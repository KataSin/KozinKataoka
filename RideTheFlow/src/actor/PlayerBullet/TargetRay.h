#pragma once
#include "../Actor.h"
#include <memory>
#include <vector>
#include "../ID.h"
#include "../Player/Player.h"
#include "../../actor/CameraActor/CameraActor.h"
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
	Line GetLine();
	Line GetSniperLine();
public:
	PlayerAttackState GetState();
	bool colFlag();
	//当たっているか
	bool GetPlayerSniperLineCol();
	//武器ごとのターゲットの動き
private:
	void MachineGun();
	void SniperGun();

private:

	PlayerAttackManager* mManager;
	CameraActor* mCamera;
	Player* mPlayer;
	//当たった場所のポジションたち
	std::vector<Vector3> mColVectorPos;
	Vector3 mColPos;
	bool mIsCol;
	//スナイパーの当たっている場所
	Vector3 mColSniperPos;
	bool mIsSniperCol;
	//プレイヤーが今持っている武器を取得
	PlayerAttackState mAttackState;
	//プレイヤーに当たったかどうか
	bool mIsPlayerCol;
};