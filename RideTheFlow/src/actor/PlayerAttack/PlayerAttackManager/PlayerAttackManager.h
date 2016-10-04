#pragma once
#include "../../Actor.h"
#include "../../PlayerBullet/PlayerBullet.h"
#include "../../CameraActor.h"

#include "../../Player.h"
class PlayerAttackManager :public Actor
{
public:
	PlayerAttackManager(IWorld& world, Actor& player);
	~PlayerAttackManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
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
	//弾に渡す情報
	BulletState bulletState;
};