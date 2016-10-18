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
	void SetPlayerState(PlayerState state) {
		playerState = state;
	}
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
	//減速処理
	void Deceleration(float& pos);
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
	//攻撃受けた時のノックバック関係
	bool isDamageMachine;
	bool isDamageSniper;
	Vector3 knockBackVelo;

	//リスポーン関係
	float respawnCount;
	bool respawnFlag;
	Vector3 respawnPoint;
	bool dropDownFlag;
	//直前に受けたダメージ
	PLAYER_NUMBER damagePlayerNumber;
	//直前に攻撃されたプレイヤーのポジション
	Vector3 damagePlayerPos;
	//スナイパーに対しての無敵関係
	float sniperCount;
	bool sniperFlag;

	Vector3 cameraPos;

	//pad情報
	int pad;

	Vector3 test;
};