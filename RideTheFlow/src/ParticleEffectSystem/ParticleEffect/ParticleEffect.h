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
	//�p�[�e�B�N�����
	ParticleEffectSystem::ParticleSetting mParticleSet;
	//�摜ID
	SPRITE_ID mId;
	//�p�[�e�B�N�����W
	Vector3 mPosition;
	//���l
	float mAlpha;
	//�p�[�e�B�N���^�C�}�[
	float mTimer;
	//�X�P�[��
	float mScale;

};