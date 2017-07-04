#pragma once
#include "../Actor.h"
#include "../ActorPtr.h"
#include <memory>
#include "../PlayerBullet\PlayerBullet.h"

#include "../ID.h"
#include "../../graphic/AnimetionClass.h"
#include "../../ParticleEffectSystem/ParticleEffectSystem.h"
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
	SNIPER_GUN,
	SHOT_GUN
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
	void SetPlayerState(PlayerState state);
	PlayerState GetPlayerState();
	PLAYER_NUMBER GetDamagePlayer();
	//弾の出現位置取得
	Vector3 GetPlayerGunPos();
	void SetRotateY(float AngleY);
public:
	//カラー
	Vector4 mColor;
private:
	void RotateMovePlayer();
	//減速処理
	void Deceleration(Vector3& pos);
	//プレイヤー個別の設定
	void PlayerNumSet(PLAYER_NUMBER num);
	//プレイヤーアニメーション
	void PlayerAnimetion(PlayerState state);
	//パーティクル情報設定
	void ParticleSetting();
	//パーティクルupdate
	void ParticleUpdate();
//プレイヤーの行動系
private:
	void Move();
	void AttackMove();
	void Jump();
	void Respawn();
private:
	//プレイヤー状態
	PlayerAttackState mAttackState;
	//1フレーム前のポジション
	Vector3 mCoppyPos;
	Vector3 mVecPos;

	//カメラ
	CameraActor* mCameraActor;
	Matrix4 mCameraMat;
	Vector3 mCameraPos;
	Vector3 mPosition;
	Vector3 mRotate;

	//プレイヤー系
	PlayerState mPlayerState;
	Vector3 mVelocity;
	Vector3 mPlayerVelocity;
	Vector3 mCurPlayerPos;
	float mAngleY;
	bool mLowStateFlag;
	float mPlayerSpeed;
	//重力フラグ
	bool mGravityFlag;
	//プレイヤージャンプ
	bool mJumpFlag;
	float mJumpCount;
	//攻撃受けた時のノックバック関係
	bool mIsDamageMachine;
	bool mIsDamageSniper;
	bool mIsDamageShot;
	Vector3 mKnockBackVelo;

	//リスポーン関係
	float mRespawnCount;
	Vector3 mRespawnPoint;
	bool mDropDownFlag;
	//直前に受けたダメージ
	PLAYER_NUMBER mDamagePlayerNumber;
	//直前に攻撃されたプレイヤーのポジション
	Vector3 mDamagePlayerPos;
	//スナイパーに対しての無敵関係
	float mSniperCount;
	bool mSniperFlag;


	//モデルID
	MODEL_ID mModelId;
	//pad情報
	int mPad;
	//ダメージUIの座標
	Vector2 mUiDamagePos;
	//ダメージバックUIの座標
	Vector2 mUiDamageBackPos;
	//アニメーションクラス
	std::shared_ptr<AnimationClass> mAnim;
	//パッドのベクトル
	Vector2 mPadVec;

	//プレイヤーパーティクルシステム情報
	ActorPtr mDashParticle;
	ParticleEffectSystem::ParticleSetting mDashParticleSet;

};