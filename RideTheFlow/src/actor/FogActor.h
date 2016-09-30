#pragma once
#include "Actor.h"
#include "../camera/Camera.h"
//ステージにかかるフォグを制御
class FogActor :public Actor
{
public:
	FogActor(IWorld& world,Camera camera);
	~FogActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 position;
	float fogTotalPower;
	float angle;
	Camera mCamera;
	//どの角度からフォグをかけるか
	float fogStartAngle;
};