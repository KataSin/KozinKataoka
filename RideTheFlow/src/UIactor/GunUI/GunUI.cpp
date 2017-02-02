#include "GunUI.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
GunUI::GunUI(IWorld & world, Vector2 position, Actor & manager) :
	UIActor(world),
	mPosition(position),
	mTurn(false)
{
	parameter.isDead = false;
	//•ÏŠ·
	mManager = dynamic_cast<PlayerAttackManager*>(&manager);

	//•ŠíŽí—ÞŽæ“¾
	mAttackState = mManager->GetState();

	//ƒvƒŒƒCƒ„[‚ª“ñl‚¾‚Á‚½‚çŠÖŒW‚È‚µ
	if (world.GetPlayerNum() == 2) return;
	//e‚Ì‰æ‘œ‚ð”½“]‚·‚é‚©‚Ç‚¤‚©
	if (mManager->GetParameter().playNumber == PLAYER_NUMBER::PLAYER_1 ||
		mManager->GetParameter().playNumber == PLAYER_NUMBER::PLAYER_3)
		mTurn = false;
	else
		mTurn = true;
}

GunUI::~GunUI()
{
}

void GunUI::Update(PLAYER_NUMBER playerNumber)
{
	mAttackState = mManager->GetState();

	mAngle += 0.1f;

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
	Vector2 size = Sprite::GetInstance().GetSize(mTexture);
	Sprite::GetInstance().Draw(mTexture, mPosition, 1.0f, Vector2(0.7f), 0.0f, true, mTurn);
}
