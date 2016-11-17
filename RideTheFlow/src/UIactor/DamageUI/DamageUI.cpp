#include "DamageUI.h"
#include "../NumberTexture/NumberTexture.h"
DamageUI::DamageUI(IWorld & world, Vector2 position, Actor * player):
	UIActor(world),
	mPosition(position)
{
	mPlayer = player;
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
	NumberTexture num(SPRITE_ID::SUUZI_SPRITE,12,24);
	num.draw(mPosition, mDamageNum, Vector4(255, 255, 255, 1));
}
