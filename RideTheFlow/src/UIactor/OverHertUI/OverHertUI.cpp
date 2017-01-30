#include "OverHertUI.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
OverHertUI::OverHertUI(IWorld & world, const Vector2 & position, Actor & manager) :
	UIActor(world),
	mAlpha(0.0f),
	mAlphaCount(0.0f),
	mFontAlpha(0.0f)
{
	parameter.isDead = false;
	parameter.position = position;
	mAttackManager = dynamic_cast<PlayerAttackManager*>(&manager);
	mTexSize = Sprite::GetInstance().GetSize(SPRITE_ID::OVER_HERT_SPRITE)/2;
}

OverHertUI::~OverHertUI()
{
}

void OverHertUI::Update(PLAYER_NUMBER playerNumber)
{
	//オーバーヒートしていたら
	if (mAttackManager->GetOverHertFlag()) {
		mAlphaCount += 75.0f*Time::DeltaTime;
		mFontAlpha += 1.0f / 2.0f*Time::DeltaTime;
		mAlpha = Math::Sin(mAlphaCount);
	}
	else {
		mAlphaCount = 0.0f;
		mFontAlpha-= 1.0f / 2.0f*Time::DeltaTime;
		mAlpha -= 1.0f / 2.0f*Time::DeltaTime;
	}
	mAlpha = Math::Clamp(mAlpha, 0.0f, 1.0f);
	mFontAlpha = Math::Clamp(mFontAlpha, 0.0f, 1.0f);
}

void OverHertUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::OVER_HERT_SPRITE, parameter.position-mTexSize, mAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::OVER_HERT_FONT_SPRITE, parameter.position-mTexSize, mFontAlpha);
}
