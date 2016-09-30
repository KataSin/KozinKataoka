#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerBullet/TargetRay.h"
#include "../../actor/Player.h"
class Target : public UIActor
{
public:
	Target(IWorld& world,TargetRay* target);
	~Target();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	PLAYER_NUMBER mPlayerNumber;
	Vector3 mPosition;
	TargetRay* mTarget;
};