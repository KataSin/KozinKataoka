#include "DamageUI.h"
#include "../NumberTexture/NumberTexture.h"
#include "../../time/Time.h"
DamageUI::DamageUI(IWorld & world, Vector2 position, Actor * player):
	UIActor(world),
	mPosition(position),
	mScale(1.0f)
{
	mPlayer = player;
	parameter.isDead = false;
}

DamageUI::~DamageUI()
{
}

void DamageUI::Update(PLAYER_NUMBER playerNumber)
{
	mDamageNum = mPlayer->GetParameter().HP;
	
}

void DamageUI::Draw() const
{
	NumberTexture num(SPRITE_ID::SUUZI_SPRITE,32,64);
	num.draw(mPosition, mDamageNum, Vector4(255, 0, 255, 1),mScale);
}
