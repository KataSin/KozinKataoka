#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
class DamageUI : public UIActor
{
public:
	DamageUI(IWorld& world,Vector2 position, Actor* player);
	~DamageUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	Actor* mPlayer;
	int mDamageNum;
	Vector2 mPosition;
	float mScale;
};