#pragma once
#include "../../Actor.h"

class StageLine :public Actor
{
public:
	StageLine(IWorld& world, Matrix4& mat);
	~StageLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//€‚Ê‚Ü‚Å‚ÌŠÔ
	float mDeadTimer;
	//“§–¾‚É‚È‚Á‚Ä‚­ŠÔ
	float mAlphaTimer;
	//“§–¾“x
	float mAlpha;
	//lineÀ•W
	Vector3 mPosition;
	//‰ñ“]Y
	float mRotateY;

};