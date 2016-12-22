#pragma once
#include "../UIActor.h"
#include "../../actor/Actor.h"
class GameTimerUI :public UIActor
{
public:
	GameTimerUI(IWorld& world, Vector2 position,float time);
	~GameTimerUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	float mGameTimer;
private:
	Vector2 mPosition;
};
