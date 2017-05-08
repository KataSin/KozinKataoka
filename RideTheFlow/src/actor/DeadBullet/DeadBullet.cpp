#include "DeadBullet.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"

DeadBullet::DeadBullet(IWorld & world,Vector3 position,PLAYER_NUMBER player) :
	Actor(world),
	coppyPos(Vector3::Zero),
	vecPos(Vector3::Zero)
{

	parameter.isDead = false;
	parameter.playNumber = player;
	parameter.id = ACTOR_ID::DEAD_BULLET_ACTOR;
	parameter.radius = 0.5f;
	parameter.mat =
		Matrix4::Scale(0)*
		Matrix4::RotateX(0),
		Matrix4::RotateY(0),
		Matrix4::RotateZ(0),
		Matrix4::Translate(position);

	Vector3 randVec = Vector3(
		Random::GetInstance().Range(-100.0f, 100.0f),
		Random::GetInstance().Range( 0.0f, 100.0f),
		Random::GetInstance().Range(-100.0f, 100.0f));

	mFrontVec = (randVec).Normalized();
	mPosition = position;
	mInitialVelocity = Random::GetInstance().Range(1.0f, 1.5f);

	vec = mFrontVec;
}

DeadBullet::~DeadBullet()
{
}

void DeadBullet::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_BULLET_COL);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYERBULLET_PLAYER_COL);

	Vector3 speed = 15.0f;
	vec += Vector3(0.0f, -0.2f, 0.0f)*speed*Time::GetInstance().deltaTime();
	mPosition += vec.Normalized()*mInitialVelocity*speed*Time::GetInstance().deltaTime();

	//下に行ったら死亡
	if (parameter.mat.GetPosition().y <= -5.0f)
		parameter.isDead = true;
	//マトリクス計算
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
}

void DeadBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_BULLET_MODEL, parameter.mat);
}

void DeadBullet::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_BULLET_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL)
	{
		parameter.isDead = true;
	}
}
