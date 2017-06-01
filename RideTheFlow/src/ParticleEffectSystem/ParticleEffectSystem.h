#pragma once
#include "../actor/Actor.h"
#include <vector>
class ParticleEffectSystem :public Actor
{
public:
	struct ParticleSetting
	{
		//パーティクルを出すかどうか
		bool isParticle = true;
		//パーティクル一つずつ出すかどうか
		bool isOneParticle = false;
		//パーティクルを一回に付き何個出すか
		int isParticleNum = 1;
		//パーティクルを出す場所
		Vector3 position;
		//パーティクルを出す場所ランダム
		Vector3 posiitonRandom;
		//パーティクルを出す速度
		float SpawnSpeed = 0.0f;
		//パーティクルを飛ばす方向
		Vector3 Vec = Vector3::Zero;
		//パーティクルを飛ばす方向のランダム値
		Vector3 VecRandom = Vector3::Zero;
		//パーティクルの初速
		Vector3 InitializeVelocity = Vector3::Zero;
		//パーティクルの減速
		float Deceleration = 0.0f;
		//パーティクル何秒たったら減速するか
		float DecelerationTime = 0.0f;
		//パーティクル何秒たったら減速するかランダム値
		float DecelerationTimeRandom = 0.0f;
		//パーティクルのα値を引く数
		float MinusAlphaNum = 0.0f;
		//パーティクル何秒たったらα値を引くか
		float MinusAlphaTime = 0.0f;
		//パーティクル何秒たったらα値を引くかランダム値
		float MinusAlphaTimeRandom = 0.0f;
		//パーティクルの寿命
		float IsDeadTime = 0.0f;
		//パーティクルのカラー
		Vector4 color = Vector4(255, 255, 255, 1);
		//パーティクルスケール値
		float scale = 1.0f;
		//パーティクルランダムスケール値
		float scaleRandom = 0.0f;
		//パーティクルテクスチャ(ランダムの場合は複数)
		std::vector<SPRITE_ID>texture;
	};

public:
	ParticleEffectSystem(IWorld& world, const ParticleSetting& particleSet);
	~ParticleEffectSystem();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	void SetParticle(ParticleSetting set) {
		mParticleSet = set;
	}

private:
	//パーティクル情報
	ParticleSetting mParticleSet;
	//パーティクルタイマー
	float mTimer;
};