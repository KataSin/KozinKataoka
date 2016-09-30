#include "Target.h"
#include "../../world/IWorld.h"
Target::Target(IWorld& world, TargetRay* target) :
	UIActor(world),
	mPosition(Vector3::Zero)
{
	mTarget = target;
	/* 初期設定 */
	parameter.isDead = false;
}

Target::~Target()
{

}

void Target::Update(PLAYER_NUMBER player)
{
	//(不具合なし)
	if (mTarget->GetParameter().playNumber == player)
	{
		mPosition =
			Vector3::ToVECTOR(ConvWorldPosToScreenPos(Vector3::ToVECTOR(mTarget->GetParameter().mat.GetPosition())));
	}
}

void Target::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::TARGET_SPRITE, Vector2(mPosition.x, mPosition.y) - Vector2(32, 16), 1.0f);
}
