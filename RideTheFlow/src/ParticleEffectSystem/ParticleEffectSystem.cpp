#include "ParticleEffectSystem.h"
#include "../world/IWorld.h"
#include "../actor/Collision.h"
#include "../time/Time.h"

#include "ParticleEffect\ParticleEffect.h"
#include "../game/Random.h"
ParticleEffectSystem::ParticleEffectSystem(IWorld& world, const ParticleSetting& particleSet) :
	Actor(world),
	mParticleSet(particleSet),
	mTimer(0.0f)
{
	parameter.isDead = false;
	mParticleSet.position += Vector3(
		Random::GetInstance().Range(-mParticleSet.posiitonRandom.x, mParticleSet.posiitonRandom.x),
		Random::GetInstance().Range(-mParticleSet.posiitonRandom.y, mParticleSet.posiitonRandom.y),
		Random::GetInstance().Range(-mParticleSet.posiitonRandom.z, mParticleSet.posiitonRandom.z));
}

ParticleEffectSystem::~ParticleEffectSystem()
{
}

void ParticleEffectSystem::Update()
{
	if (mParticleSet.isOneParticle) {
		//ひとつずつ出す処理
		if (mParticleSet.isParticle) {
			for (int i = 0; i < mParticleSet.isParticleNum; i++) {
				//ランダム座標設定
				Vector3 rand = Vector3(
					Random::GetInstance().Range(-mParticleSet.posiitonRandom.x, mParticleSet.posiitonRandom.x),
					Random::GetInstance().Range(-mParticleSet.posiitonRandom.y, mParticleSet.posiitonRandom.y),
					Random::GetInstance().Range(-mParticleSet.posiitonRandom.z, mParticleSet.posiitonRandom.z));
				mParticleSet.position += rand;
				world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleEffect>(world, mParticleSet));
			}
			mParticleSet.isParticle = false;
		}
		return;
	}
	//連続で出す場合
	if (!mParticleSet.isParticle)return;
	mTimer += Time::GetInstance().deltaTime();
	if (mTimer >= mParticleSet.SpawnSpeed) {
		mTimer = 0.0f;
		//ランダム座標設定
		for (int i = 0; i < mParticleSet.isParticleNum; i++) {
			Vector3 rand = Vector3(
				Random::GetInstance().Range(-mParticleSet.posiitonRandom.x, mParticleSet.posiitonRandom.x),
				Random::GetInstance().Range(-mParticleSet.posiitonRandom.y, mParticleSet.posiitonRandom.y),
				Random::GetInstance().Range(-mParticleSet.posiitonRandom.z, mParticleSet.posiitonRandom.z));
			mParticleSet.position += rand;
			world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleEffect>(world, mParticleSet));
		}
	}
}

void ParticleEffectSystem::Draw() const
{
}

void ParticleEffectSystem::OnCollide(Actor & other, CollisionParameter colpara)
{
}