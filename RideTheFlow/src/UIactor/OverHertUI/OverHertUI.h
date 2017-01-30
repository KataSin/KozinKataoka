#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
class OverHertUI : public UIActor
{
public:
	OverHertUI(IWorld& world, const Vector2& position, Actor& manager);
	~OverHertUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//�A�^�b�N�}�l�[�W���[
	PlayerAttackManager* mAttackManager;
	//���l
	float mAlpha;
	//�t�H���g���l
	float mFontAlpha;
	//���l�p�J�E���g
	float mAlphaCount;
	//�e�N�X�`���T�C�Y
	Vector2 mTexSize;
};