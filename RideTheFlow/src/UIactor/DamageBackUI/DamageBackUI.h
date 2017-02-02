#pragma once
#include "../UIActor.h"
#include "../../actor/Player.h"
class DamageBackUI : public UIActor
{
public:
	DamageBackUI(IWorld& world, const Vector2& position, Actor& player);
	~DamageBackUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	Actor* mPlayer;
	Vector2 mPosition;
	//フォントのテクスチャサイズ
	Vector2 mFontSize;
	//バックのテクスチャサイズ
	Vector2 mDamageBackSize;
	//フォントの座標
	Vector2 mFontPos;
	//バックのサイズ
	Vector2 mScale;
	SPRITE_ID mId;
	float mAlpha;

};