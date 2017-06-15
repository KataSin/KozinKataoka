#include "Target.h"
#include "../../world/IWorld.h"
#include "../../actor/PlayerBullet/TargetRay.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
Target::Target(IWorld& world, Actor& attackManager,Actor& target) :
	UIActor(world)
{
	mAttackManager =static_cast<PlayerAttackManager*>(&attackManager);
	mTarget = static_cast<TargetRay*>(&target);
	/* 初期設定 */
	parameter.isDead = false;
	parameter.position = Vector2::Zero;
	parameter.playerNum = mAttackManager->GetParameter().playNumber;
}

Target::~Target()
{

}

void Target::Update(PLAYER_NUMBER player)
{
	mPlayer = dynamic_cast<Player*>(world.GetPlayer(mAttackManager->GetParameter().playNumber).get());
	//(不具合なし)
	if (player==parameter.playerNum)
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
	else if (mTarget->GetState() == PlayerAttackState::SNIPER_GUN) {
		Sprite::GetInstance().Draw(SPRITE_ID::SNEPER_SPRITE, parameter.position - Vector2(19.0f / 2.0f), 1.0f);
		
		if (mAttackManager->GetChargeCount().doCharge) {
			Sprite::GetInstance().DrawGaugeCircle(SPRITE_ID::SUNIPER_TARGET_CIRCLE_SPRITE, parameter.position - Vector2(13, 13), mPlayer->mColor, mAttackManager->GetChargeCount().chargeSniperCount);
			if (mTarget->GetPlayerSniperLineCol())
				Sprite::GetInstance().Draw(SPRITE_ID::SUNIPER_TARGET_YES_SPRITE, parameter.position - Vector2(13, 13), 1.0f);
		}
	}
}
