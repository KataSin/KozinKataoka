#pragma once
#include "Actor.h"
#include <memory>
#include "PlayerBullet\PlayerBullet.h"
#include "CameraActor.h"
#include "ID.h"

enum PlayerState
{
	PLAYERSTOP,
	PLAYERWALK,
	PLAYERDASH,
	PLAYERJUMP,
	PLAYERATTACK,
	PLAYERSNIPERATTACK,
	PLAYERATTACKCHARGE,
	PLAYERDAMAGE,
	PLAYERRESPAWN
};
enum PlayerAttackState
{
	MACHINE_GUN,
	SNIPER_GUN
};
//謎
class CameraActor;

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world,Vector3 position,float rotateY,PLAYER_NUMBER player);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	PlayerState GetPlayerState();
	PLAYER_NUMBER GetDamagePlayer();
	//弾の出現位置取得
	Vector3 GetPlayerGunPos() {
		return parameter.mat.GetPosition() + Vector3(0.0f, 2.0f, 0.0f);
	}
	//今装備している武器を取得
	PlayerAttackState GetAttackState()
	{
		return attackState;
	}
	void SetRotateY(float AngleY)
	{
		angleY = AngleY;
	}
private:
	void RotateMovePlayer();
//プレイヤーの行動系
private:
	void Move();
	void AttackMove();
	void Jump();
	void Respawn();
private:
	//プレイヤー状態
	PlayerAttackState attackState;

	//1フレーム前のポジション
	Vector3 coppyPos;
	Vector3 vecPos;

	//カメラ
	CameraActor* cameraActor;
	Matrix4 cameraMat;

	Vector3 mPosition;
	Vector3 mRotate;

	//プレイヤーの状態
	PlayerState playerState;
	Matrix4 playerModelMat;
	Vector3 mVelocity;
	float angleY;
	bool lowStateFlag;
	float playerSpeed;
	//重力フラグ
	bool gravityFlag;

	//プレイヤージャンプ
	bool jumpFlag;
	float jumpCount;

	//リスポーン関係
	float respawnCount;
	bool respawnFlag;
	Vector3 respawnPoint;

	//直前に受けたダメージ
	PLAYER_NUMBER damagePlayerNumber;

	Vector3 cameraPos;

	//pad情報
	int pad;

	Vector3 test;
};