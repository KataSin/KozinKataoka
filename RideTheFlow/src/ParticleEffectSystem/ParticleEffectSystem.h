#pragma once
#include "../actor/Actor.h"
#include <vector>
class ParticleEffectSystem :public Actor
{
public:
	struct ParticleSetting
	{
		//�p�[�e�B�N�����o�����ǂ���
		bool isParticle = true;
		//�p�[�e�B�N������o�����ǂ���
		bool isOneParticle = false;
		//�p�[�e�B�N�������ɕt�����o����
		int isParticleNum = 1;
		//�p�[�e�B�N�����o���ꏊ
		Vector3 position;
		//�p�[�e�B�N�����o���ꏊ�����_��
		Vector3 posiitonRandom;
		//�p�[�e�B�N�����o�����x
		float SpawnSpeed = 0.0f;
		//�p�[�e�B�N�����΂�����
		Vector3 Vec = Vector3::Zero;
		//�p�[�e�B�N�����΂������̃����_���l
		Vector3 VecRandom = Vector3::Zero;
		//�p�[�e�B�N���̏���
		Vector3 InitializeVelocity = Vector3::Zero;
		//�p�[�e�B�N���̌���
		float Deceleration = 0.0f;
		//�p�[�e�B�N�����b�������猸�����邩
		float DecelerationTime = 0.0f;
		//�p�[�e�B�N�����b�������猸�����邩�����_���l
		float DecelerationTimeRandom = 0.0f;
		//�p�[�e�B�N���̃��l��������
		float MinusAlphaNum = 0.0f;
		//�p�[�e�B�N�����b�������烿�l��������
		float MinusAlphaTime = 0.0f;
		//�p�[�e�B�N�����b�������烿�l�������������_���l
		float MinusAlphaTimeRandom = 0.0f;
		//�p�[�e�B�N���̎���
		float IsDeadTime = 0.0f;
		//�p�[�e�B�N���̃J���[
		Vector4 color = Vector4(255, 255, 255, 1);
		//�p�[�e�B�N���X�P�[���l
		float scale = 1.0f;
		//�p�[�e�B�N�������_���X�P�[���l
		float scaleRandom = 0.0f;
		//�p�[�e�B�N���e�N�X�`��(�����_���̏ꍇ�͕���)
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
	//�p�[�e�B�N�����
	ParticleSetting mParticleSet;
	//�p�[�e�B�N���^�C�}�[
	float mTimer;
};