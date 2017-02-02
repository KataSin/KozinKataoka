#include "DamageBackUI.h"
#include "../../time/Time.h"
#include "../../world/IWorld.h"
DamageBackUI::DamageBackUI(IWorld & world, const Vector2& position, Actor& player) :
	UIActor(world),
	mPosition(position),
	mFontPos(position),
	mAlpha(0.0f),
	mId(SPRITE_ID::SINUYO_SPRITE),
	mScale(1)
{
	parameter.isDead = false;
	mPlayer = &player;
	mFontSize = Sprite::GetInstance().GetSize(SPRITE_ID::SINDA_SPRITE);
	mDamageBackSize = Sprite::GetInstance().GetSize(SPRITE_ID::DAMAGE_BACK_SPRITE);
	//プレイヤーが二人の時はX軸を2倍
	if (world.GetPlayerNum() == 2)
		mScale = Vector2(2, 1);

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
	Sprite::GetInstance().Draw(SPRITE_ID::DAMAGE_BACK_SPRITE, mPosition, Vector4(255, 255, 255, 1), mDamageBackSize/2, mAlpha, mScale, 0.0f);
	Sprite::GetInstance().Draw(mId, mFontPos, Vector4(255,255,255,1),mFontSize/2,mAlpha,Vector2(1),0.0f);
}
