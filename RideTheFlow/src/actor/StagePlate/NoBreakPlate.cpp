#include "NoBreakPlate.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Model.h"
NoBreakPlate::NoBreakPlate(IWorld & world, const Vector3 & position):
	Actor(world),
	mPosition(position)
{
	parameter.isDead = false;
	parameter.mat = 
		Matrix4::Scale(1.0f)*
		Matrix4::Translate(position);
}

NoBreakPlate::~NoBreakPlate()
{
}

void NoBreakPlate::Update()
{
	//‚ ‚½‚è”»’è
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLATE_PLAYER_COL);
	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::Translate(mPosition);
}

void NoBreakPlate::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::NOBREAKPLATE_MODEL, parameter.mat, 1.0f);
}

void NoBreakPlate::OnCollide(Actor & other, CollisionParameter colpara)
{
}
