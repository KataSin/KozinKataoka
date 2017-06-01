#include "ParticleEffect.h"
#include "../../world/IWorld.h"
#include "../../actor/Collision.h"
#include "../../graphic/Sprite.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
ParticleEffect::ParticleEffect(IWorld & world, const ParticleEffectSystem::ParticleSetting & particleSet) :
	Actor(world),
	mParticleSet(particleSet),
	mTimer(0.0f)
{
	//������
	parameter.isDead = false;
	mPosition = particleSet.position;
	mAlpha = 1.0f;
	mScale = mParticleSet.scale+Random::GetInstance().Range(-mParticleSet.scaleRandom,mParticleSet.scale);

	//�ړ�����
	Vector3 randVec = Vector3(
		Random::GetInstance().Range(-mParticleSet.VecRandom.x, mParticleSet.VecRandom.x),
		Random::GetInstance().Range(-mParticleSet.VecRandom.y, mParticleSet.VecRandom.y),
		Random::GetInstance().Range(-mParticleSet.VecRandom.z, mParticleSet.VecRandom.z)
		);
	Vector3 vec = (mParticleSet.Vec + randVec).Normalized()*mParticleSet.InitializeVelocity;
	mParticleSet.Vec = vec;
	//��������
	mParticleSet.DecelerationTimeRandom = 
		Random::GetInstance().Range(-mParticleSet.DecelerationTimeRandom, mParticleSet.DecelerationTimeRandom);
	mParticleSet.DecelerationTime += mParticleSet.DecelerationTimeRandom;
	//���l����
	mParticleSet.MinusAlphaTimeRandom =
		Random::GetInstance().Range(-mParticleSet.MinusAlphaTimeRandom, mParticleSet.MinusAlphaTimeRandom);
	mParticleSet.MinusAlphaTime += mParticleSet.DecelerationTimeRandom;
	//�e�N�X�`���o�^
	mId = mParticleSet.texture[Random::GetInstance().Range(0, mParticleSet.texture.size() - 1)];
}

ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::Update()
{
	//�^�C������
	mTimer += Time::GetInstance().deltaTime();


	//�ړ�����
	mPosition += mParticleSet.Vec*Time::GetInstance().deltaTime();
	
	//��������
	if (mTimer >= mParticleSet.DecelerationTime) {
		mParticleSet.Vec -= (mParticleSet.Vec.Normalized()*mParticleSet.Deceleration)*Time::GetInstance().deltaTime();
	}
	//������
	if (mTimer >= mParticleSet.MinusAlphaTime) {
		mAlpha -= mParticleSet.MinusAlphaNum*Time::GetInstance().deltaTime();
	}

	//����
	if (mTimer >= mParticleSet.IsDeadTime)
		parameter.isDead = true;
}

void ParticleEffect::Draw() const
{
	Sprite::GetInstance().DrawBillBoard(mId, mPosition, Vector2::Zero,mScale, 1.0f,mAlpha,mParticleSet.color);
}

void ParticleEffect::OnCollide(Actor & other, CollisionParameter colpara)
{
}
