#include "DeadBulletManager.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "DeadBullet.h"
const int bulletNum = 10;

DeadBulletManager::DeadBulletManager(IWorld & world,Vector3 position,PLAYER_NUMBER player) :
	Actor(world)
{
	parameter.isDead = false;
	for (int i = 0; i <= bulletNum; i++)
	{
		world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<DeadBullet>(world, position, player));
	}
}

DeadBulletManager::~DeadBulletManager()
{
}

void DeadBulletManager::Update()
{
	parameter.isDead = true;
}

void DeadBulletManager::Draw() const
{
}

void DeadBulletManager::OnCollide(Actor & other, CollisionParameter colpara)
{
}
