#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>

class SelectSceneCamera :public Actor
{
public:
	SelectSceneCamera(IWorld& word, const Vector3& position,const Vector3& target);
	~SelectSceneCamera();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	Vector3 mTarget;
};