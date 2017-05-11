#include "ResultPlayer.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include "../../graphic/Model.h"
#include "../../graphic/AnimetionClass.h"
ResultPlayer::ResultPlayer(IWorld & word, const Vector3 & position, const MODEL_ID & player,ANIMATION anim) :
	Actor(world),
	mPosition(position),
	mModelId(player)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(position);

	mAnim = std::make_shared<AnimationClass>(this, anim, player);
}

ResultPlayer::~ResultPlayer()
{
}

void ResultPlayer::Update()
{
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
	mAnim->update();
}

void ResultPlayer::Draw() const
{
	mAnim->draw();
}

void ResultPlayer::OnCollide(Actor & other, CollisionParameter colpara)
{
}
