#pragma once
#include "../UIActor.h"
#include "../../actor/Player.h"

class PlayerAttackManager;
class TargetRay;
class Target : public UIActor
{
public:
	Target(IWorld& world, Actor& attackManager, Actor& target);
	~Target();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	PLAYER_NUMBER mPlayerNumber;
	PlayerAttackManager* mAttackManager;
	TargetRay* mTarget;
	Player* mPlayer;
};