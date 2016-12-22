#include "Target.h"
#include "../../world/IWorld.h"
Target::Target(IWorld& world, TargetRay* target) :
	UIActor(world)
{
	mTarget = target;
	/* 初期設定 */
	parameter.isDead = false;
	parameter.position = Vector2::Zero;
	parameter.playerNum = target->GetParameter().playNumber;
}

Target::~Target()
{

}

void Target::Update(PLAYER_NUMBER player)
{
	mPlayer = dynamic_cast<Player*>(world.GetPlayer(mTarget->GetParameter().playNumber).get());
	//(不具合なし)
	if (mTarget->GetParameter().playNumber == player)
	{
		parameter.position =
			Vector3::ToVECTOR(ConvWorldPosToScreenPos(Vector3::ToVECTOR(mTarget->GetParameter().mat.GetPosition())));
	}
}

void Target::Draw() const
{
	//リスポーン中は表示しない
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN)return;
	if (mTarget->GetState() == PlayerAttackState::MACHINE_GUN|| mTarget->GetState() == PlayerAttackState::SHOT_GUN)
		Sprite::GetInstance().Draw(SPRITE_ID::TARGET_SPRITE, parameter.position - Vector2(32, 16), 1.0f);
	else if(mTarget->GetState() == PlayerAttackState::SNIPER_GUN)
		Sprite::GetInstance().Draw(SPRITE_ID::SNEPER_SPRITE, parameter.position - Vector2(19.0f/2.0f), 1.0f);
}
