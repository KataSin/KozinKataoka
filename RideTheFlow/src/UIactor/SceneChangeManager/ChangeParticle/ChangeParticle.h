#pragma once
#include "../../UIActor.h"
class ChangeParticle :public UIActor {
public:
	ChangeParticle(IWorld& world,const Vector2& position, const Vector2& vec,float angle,float deadTime,float size);
	~ChangeParticle();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	Vector2 mPosition;
	Vector2 mVec;
	Vector2 mCenter;
	float mAngle;
	float mPlusAngle;
	float mDeadTime;
	float mTime;
	float mAlpha;
	float mSize;
};