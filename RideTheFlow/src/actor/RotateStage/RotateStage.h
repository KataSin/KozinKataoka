#pragma once
#pragma once
#include "../Actor.h"
#include "../ID.h"
class RotateStage :public Actor
{
public:
	RotateStage(IWorld& world, const Vector3& position);
	~RotateStage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	Matrix4 mSkymat;
	Vector3 mPosition;
	float mRotateY;
};