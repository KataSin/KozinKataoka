#include "AnimActor.h"
#include "../../world/IWorld.h"
#include "../Collision.h"
#include "../../graphic/Model.h"
#include "../../graphic/AnimetionClass.h"
AnimActor::AnimActor(IWorld & word, const Vector3 & position, const PLAYER_NUMBER& player, ANIMATION anim) :
	Actor(world),
	mPosition(position)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(position);
	parameter.playNumber = player;

	switch (parameter.playNumber)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		mModelId = MODEL_ID::PLAYER1_MODEL;
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		mModelId = MODEL_ID::PLAYER2_MODEL;
		break;
	}
	case PLAYER_NUMBER::PLAYER_3:
	{
		mModelId = MODEL_ID::PLAYER3_MODEL;
		break;
	}
	case PLAYER_NUMBER::PLAYER_4:
	{
		mModelId = MODEL_ID::PLAYER4_MODEL;
		break;
	}
	}

	mAnim = std::make_shared<AnimationClass>(this, anim, mModelId,30.0f);
}

AnimActor::AnimActor(IWorld & word, const Matrix4 & mat, const MODEL_ID & modelId, ANIMATION anim) :
	Actor(world)
{
	parameter.isDead = false;
	parameter.mat = mat;
	mModelId = modelId;
	mAnim = std::make_shared<AnimationClass>(this, anim, mModelId);
}

AnimActor::~AnimActor()
{
}

void AnimActor::Update()
{
	mAnim->update();
}

void AnimActor::Draw() const
{
	mAnim->draw();
}

void AnimActor::OnCollide(Actor & other, CollisionParameter colpara)
{
}