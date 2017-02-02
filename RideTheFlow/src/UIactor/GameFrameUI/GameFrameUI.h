#pragma once
#include "../UIActor.h"

class GameFrameUI : public UIActor
{
public:
	GameFrameUI(IWorld& world, const Vector2& position,int playNum);
	~GameFrameUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	Vector2 mPosition;
	int mPlayNum;
};