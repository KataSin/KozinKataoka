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
	//�t�H���g�̃e�N�X�`���T�C�Y
	Vector2 mFontSize;
	//�o�b�N�̃e�N�X�`���T�C�Y
	Vector2 mDamageBackSize;
	//�t�H���g�̍��W
	Vector2 mFontPos;
	//�o�b�N�̃T�C�Y
	Vector2 mScale;
	SPRITE_ID mId;
	float mAlpha;

};