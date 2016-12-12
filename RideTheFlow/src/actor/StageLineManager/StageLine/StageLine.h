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
	//���ʂ܂ł̎���
	float mDeadTimer;
	//�����ɂȂ��Ă�����
	float mAlphaTimer;
	//�����x
	float mAlpha;
	//line���W
	Vector3 mPosition;
	//��]Y
	float mRotateY;

};