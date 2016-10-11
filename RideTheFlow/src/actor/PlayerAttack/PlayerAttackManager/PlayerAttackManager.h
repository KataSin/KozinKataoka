#pragma once
#include "../../Actor.h"
#include "../../PlayerBullet/PlayerBullet.h"
#include "../../CameraActor.h"

#include "../../Player.h"

struct SniperState
{
	//チャージ量
	float chargeSniperCount;
	//当たるかどうか
	bool isColSniperLine;
	//チャージしているか
	bool doCharge;
};

class PlayerAttackManager :public Actor
{
public:
	PlayerAttackManager(IWorld& world, Actor& player);
	~PlayerAttackManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	PlayerAttackState GetState()
	{
		return attackState;
	}
	SniperState GetChargeCount()
	{
		return mSniperState;
	}
private:
	void PlayerAttack(PlayerAttackState state);
	void MachineGun();
	void SniperGun();
private:
	//カメラアクター
	CameraActor* mCamera;
	//プレイヤー
	Actor* mPlayer;
	//パッドの数字
	int pad;
	//装備している武器
	PlayerAttackState attackState;
	//オーバーヒートカウント
	float overHertCount;
	//スナイパーの弾情報
	SniperState mSniperState;
	//スナイパーのあたり判定のカウント
	float isColSniperCount;
	//弾に渡す情報
	BulletState bulletState;
	//スナイパーのフラグ
	bool initSniperFalg;
};