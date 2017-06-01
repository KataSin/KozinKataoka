#pragma once
#include "../../actor/Actor.h"
#include "../ParticleEffectSystem.h"
class ParticleEffect:public Actor
{
public:
	ParticleEffect(IWorld& world, const ParticleEffectSystem::ParticleSetting& particleSet);
	~ParticleEffect();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//パーティクル情報
	ParticleEffectSystem::ParticleSetting mParticleSet;
	//画像ID
	SPRITE_ID mId;
	//パーティクル座標
	Vector3 mPosition;
	//α値
	float mAlpha;
	//パーティクルタイマー
	float mTimer;
	//スケール
	float mScale;

};