#include "ParticleManager.h"
#include "../../game/Random.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ParticleManager/Particle/Particle.h"
ParticleManager::ParticleManager(IWorld & world, Vector3 position, Vector4 color) :
	Actor(world)
{
	parameter.isDead = false;
	for (int x = 0; x <= 5; x++) {
		for (int y = 0; y <= 5; y++) {
			Vector3 randVec = Vector3(Random::GetInstance().Range(-3, 3), Random::GetInstance().Range(1, 6), Random::GetInstance().Range(-3, 3));
			Vector3 pos=position + Vector3(4.0f*x, -0.5f, 4.0f*y) - Vector3(10, 0.5, 10);;
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
