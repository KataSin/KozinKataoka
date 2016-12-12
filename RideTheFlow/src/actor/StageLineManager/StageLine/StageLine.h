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
	//死ぬまでの時間
	float mDeadTimer;
	//透明になってく時間
	float mAlphaTimer;
	//透明度
	float mAlpha;
	//line座標
	Vector3 mPosition;
	//回転Y
	float mRotateY;

};