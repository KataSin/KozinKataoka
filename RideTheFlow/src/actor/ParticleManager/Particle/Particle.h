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
	//位置
	Vector3 mPosition;
	//カラー
	Vector4 mColor;
	//初速度
	Vector3 mInitialVelocity;
	//ベクトル
	Vector3 mVec;
	//消える時間
	float mDeadTime;
	//α値
	float mAlpha;
};