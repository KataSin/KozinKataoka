#include "RespawnPoint.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../time/Time.h"
#include "../graphic/Anime.h"
#include "../math/Math.h"
#include "../camera/Camera.h"
#include "../math/Quaternion.h"
#include "../game/Random.h"
#include "../input/GamePad.h"
#include "../sound/Sound.h"
#include "Player.h"

RespawnPoint::RespawnPoint(IWorld & world, Vector3 position,float rotateY, PLAYER_NUMBER player):
	Actor(world),
	mPlayerNum(player),
	mPosition(position)
{
	parameter.isDead = false;
	parameter.playNumber = player;
	parameter.radius = 10.0f;
	parameter.mat = 
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(rotateY)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(position);
	world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(world, position,rotateY,
		player));

}

RespawnPoint::~RespawnPoint()
{
}

void RespawnPoint::Update()
{
	parameter.mat =
		Matrix4::Scale(20)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition+Vector3(0.0f,0.5f,0.0f));
}

void RespawnPoint::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::RESPAWN_MODEL, parameter.mat);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 10, 1, 1, FALSE);
}

void RespawnPoint::OnCollide(Actor & other, CollisionParameter colpara)
{

}
