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
	//�ʒu
	Vector3 mPosition;
	//�����x
	Vector3 mInitialVelocity;
};