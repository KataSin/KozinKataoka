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
	SPRITE_ID mId;
	float mAlpha;

};