#include "SniperBullet.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"

SniperBullet::SniperBullet(IWorld & world, Player & player):
	Actor(world)
{
	parameter.isDead = false;
	parameter.playNumber = player.GetParameter().playNumber;
}

SniperBullet::~SniperBullet()
{
}

void SniperBullet::Update()
{
	//ƒeƒXƒg
	int a = 0;
}

void SniperBullet::Draw() const
{
}

void SniperBullet::OnCollide(Actor & other, CollisionParameter colpara)
{
}
