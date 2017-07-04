#pragma once
#include "../../Actor.h"
#include "../../Player/Player.h"
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
	PlayerAttackState GetState();
	SniperState GetChargeCount();
	float GetOverHertCount();
	//オーバーヒートしているか
	bool GetOverHertFlag();
	//攻撃しているか？
	bool GetIsAttack();
private:
	void PlayerAttack(PlayerAttackState state);
	void PlayerNumSet(PLAYER_NUMBER num);
	void MachineGun();
	void SniperGun();
	void ShotGun();
	//パーティクルセット
	void ParticleSet();
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
	int mPad;
	//プレイヤー武器int型
	int mAttacStateInt;
	//装備している武器
	PlayerAttackState mAttackState;
	//マシンガン連続攻撃カウント
	float mMachineAttackCount;
	//オーバーヒートカウント
	float mOverHertCount;
	//オーバーヒートフラグ
	bool mOverHertFlag;
	//スナイパーの弾情報
	SniperState mSniperState;
	//スナイパーのあたり判定のカウント
	float mIsColSniperCount;
	//スナイパーのフラグ
	bool mInitSniperFalg;
	//ショットガン連続攻撃カウント
	float mShotAttackCount;
	//攻撃しているか？
	bool mAttackFlag;
	//オーバーヒート冷め始める時間
	float mCoolHertCount;
	//uiの場所
	Vector2 mUiPos;
	//オーバーヒートの座標
	Vector2 mOverHertUiPos;
	//色情報
	Vector4 mColor;

	//パーティクル
	ActorPtr mAttackParticle;
	ParticleEffectSystem::ParticleSetting mAttackParticleSet;

};