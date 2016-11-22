#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>
class ParticleManager:public Actor
{
public:
	ParticleManager(IWorld& world, Vector3 position, Vector4 color);
	~ParticleManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//à íu
	Vector3 mPosition;
	//èâë¨ìx
	Vector3 mInitialVelocity;
};