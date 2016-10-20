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
	float GetOverHertCount()
	{
		return overHertCount;
	}
private:
	void PlayerAttack(PlayerAttackState state);
	void MachineGun();
	void SniperGun();
	void ShotGun();
private:
	//カメラアクター
	CameraActor* mCamera;
	//プレイヤー
	Player* mPlayer;
	//パッドの数字
	int pad;
	//装備している武器
	PlayerAttackState attackState;
	//マシンガン連続攻撃カウント
	float machineAttackCount;
	//オーバーヒートカウント
	float overHertCount;
	//オーバーヒートフラグ
	bool overHertFlag;
	//スナイパーの弾情報
	SniperState mSniperState;
	//スナイパーのあたり判定のカウント
	float isColSniperCount;
	//スナイパーのフラグ
	bool initSniperFalg;
	//ショットガン連続攻撃カウント
	float shotAttackCount;
	//攻撃しているか？
	bool attackFlag;
	//オーバーヒート冷め始める時間
	float coolHertCount;
};