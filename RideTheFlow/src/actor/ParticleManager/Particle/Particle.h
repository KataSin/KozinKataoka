#pragma once
#pragma once
#include "../../Actor.h"
#include <memory>
#include "../../ID.h"

class Particle :public Actor
{
public:
	Particle(IWorld& world, Vector3 position,Vector3 vec, Vector4 color);
	~Particle();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	void Deceleration(float& pos);
private:
	//�ʒu
	Vector3 mPosition;
	//�J���[
	Vector4 mColor;
	//�����x
	Vector3 mInitialVelocity;
	//�x�N�g��
	Vector3 mVec;
	//�����鎞��
	float mDeadTime;
	//���l
	float mAlpha;
};