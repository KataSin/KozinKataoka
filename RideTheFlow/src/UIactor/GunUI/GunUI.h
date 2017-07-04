#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player/Player.h"
class GunUI : public UIActor
{
public:
	GunUI(IWorld& world, Vector2 position, Actor& manager);
	~GunUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	PlayerAttackState mAttackState;
	Vector2 mPosition;
	Vector4 mColor;
	PlayerAttackManager* mManager;
	SPRITE_ID mTexture;
	//‰æ‘œ‚ð”½“]‚·‚é‚©‚Ç‚¤‚©
	bool mTurn;
	//‰æ‘œ‚Ì‰ñ“]
	float mAngle;
};