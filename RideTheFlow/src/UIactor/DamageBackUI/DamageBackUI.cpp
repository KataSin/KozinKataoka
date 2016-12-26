#include "DamageBackUI.h"
#include "../../time/Time.h"
DamageBackUI::DamageBackUI(IWorld & world, const Vector2& position, Actor& player) :
	UIActor(world),
	mPosition(position),
	mAlpha(0.0f),
	mId(SPRITE_ID::SINUYO_SPRITE)
{
	parameter.isDead = false;
	mPlayer = &player;
}

DamageBackUI::~DamageBackUI()
{
}

void DamageBackUI::Update(PLAYER_NUMBER playerNumber)
{
	int hp = mPlayer->GetParameter().HP;
	mAlpha = hp / 2000.0f;
	if (mPlayer->GetParameter().isRespawn) {
		mAlpha = 1.0f;
		mId = SPRITE_ID::SINDA_SPRITE;
	}
}

void DamageBackUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::DAMAGE_BACK_SPRITE,mPosition,mAlpha);
	Sprite::GetInstance().Draw(mId, mPosition, mAlpha);
}
