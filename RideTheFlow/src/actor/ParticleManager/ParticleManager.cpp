#include "ParticleManager.h"
#include "../../game/Random.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ParticleManager/Particle/Particle.h"
ParticleManager::ParticleManager(IWorld& world, 
	const Vector3& position,const Vector3& positionPlus, 
	const Vector4& color,int particleNum, 
	const Vector3& maxRand, const Vector3& minRand, 
	const Vector3& hosei) :
	Actor(world)
{
	parameter.isDead = false;
	for (int x = 0; x <= particleNum; x++) {
		for (int y = 0; y <= particleNum; y++) {
			Vector3 randVec = Vector3(
				Random::GetInstance().Range(minRand.x,maxRand.x),
				Random::GetInstance().Range(minRand.y, maxRand.y),
				Random::GetInstance().Range(minRand.z, maxRand.z));
			Vector3 pos = position + Vector3(positionPlus.x*x, positionPlus.y, positionPlus.z*y)-hosei;
			world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<Particle>(world, pos, randVec, color));
		}
	}
	parameter.isDead = true;
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Update()
{

}

void ParticleManager::Draw() const
{
}

void ParticleManager::OnCollide(Actor & other, CollisionParameter colpara)
{
}
