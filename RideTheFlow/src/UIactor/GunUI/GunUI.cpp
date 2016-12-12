#include "GunUI.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
GunUI::GunUI(IWorld & world, Vector2 position, Actor * manager):
	UIActor(world),
	mPosition(position)
{
	//•ÏŠ·
	mManager = dynamic_cast<PlayerAttackManager*>(manager);
	//•ŠíŽí—ÞŽæ“¾
	mAttackState = mManager->GetState();
}

GunUI::~GunUI()
{
}

void GunUI::Update(PLAYER_NUMBER playerNumber)
{
	mAttackState = mManager->GetState();

	switch (mAttackState)
	{
	case PlayerAttackState::MACHINE_GUN:
	{
		mTexture = SPRITE_ID::MACHINE_UI_SPRITE;
		break;
	}
	case PlayerAttackState::SHOT_GUN:
	{
		mTexture = SPRITE_ID::SHOT_UI_SPRITE;
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		mTexture = SPRITE_ID::SNEPER_UI_SPRITE;
		break;
	}
	}

}

void GunUI::Draw() const
{
	Sprite::GetInstance().Draw(
		mTexture,mPosition+(Sprite::GetInstance().GetSize(mTexture)/2));
}
