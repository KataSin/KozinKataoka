#include "Target.h"
#include "../../world/IWorld.h"
Target::Target(IWorld& world, TargetRay* target) :
	UIActor(world),
	mPosition(Vector3::Zero)
{
	mTarget = target;
	/* ‰ŠúÝ’è */
	parameter.isDead = false;
}

Target::~Target()
{

}

void Target::Update(PLAYER_NUMBER player)
{
	//(•s‹ï‡‚È‚µ)
	if (mTarget->GetParameter().playNumber == player)
	{
		mPosition =
			Vector3::ToVECTOR(ConvWorldPosToScreenPos(Vector3::ToVECTOR(mTarget->GetParameter().mat.GetPosition())));
	}
}

void Target::Draw() const
{
	if (mTarget->GetState() == PlayerAttackState::MACHINE_GUN)
		Sprite::GetInstance().Draw(SPRITE_ID::TARGET_SPRITE, Vector2(mPosition.x, mPosition.y) - Vector2(32, 16), 1.0f);
	else if(mTarget->GetState() == PlayerAttackState::SNIPER_GUN)
		Sprite::GetInstance().Draw(SPRITE_ID::SNEPER_SPRITE, Vector2(mPosition.x, mPosition.y) - Vector2(19.0f/2.0f), 1.0f);
}
