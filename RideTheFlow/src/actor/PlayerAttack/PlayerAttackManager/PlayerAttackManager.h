#pragma once
#include "../../Actor.h"
#include "../../Player.h"
class CameraActor;
class PlayerGun;
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
	//オーバーヒートしているか
	bool GetOverHertFlag()
	{
		return overHertFlag;
	}
	//攻撃しているか？
	bool GetIsAttack()
	{
		return attackFlag;
	}
private:
	void PlayerAttack(PlayerAttackState state);
	void PlayerNumSet(PLAYER_NUMBER num);
	void MachineGun();
	void SniperGun();
	void ShotGun();
	//パーティクルセット
	void ParticleSet();
	////パーティクルアップデート
	//void ParticleUpdate();
	//パーティクル追加
	void AddParticle();
private:
	//カメラアクター
	CameraActor* mCamera;
	//プレイヤー
	Player* mPlayer;
	//武器アクター
	ActorPtr mGunPlayer;
	//武器のマトリクス
	Matrix4 mGunMat;
	//パッドの数字
	int pad;
	//プレイヤー武器int型
	int attacStateInt;
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
	//uiの場所
	Vector2 uiPos;
	//オーバーヒートの座標
	Vector2 mOverHertUiPos;
	//色情報
	Vector4 mColor;

	//パーティクル
	ActorPtr mAttackParticle;
	ParticleEffectSystem::ParticleSetting mAttackParticleSet;

};